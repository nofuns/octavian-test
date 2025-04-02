#include "Reel.hpp"

#include "Random.hpp"

Reel::Reel(const std::vector<sf::Sprite>& sprites, Random& random)
    : m_symbols(), m_symbolsPos(), m_position({ 0, 0 }), m_isRolling(false), m_isAligning(false), m_velocity(700.f), m_alignOffset(0.f)
{
    
    for (size_t i = 0; i < sprites.size(); ++i) {
        m_symbols.push_back(ReelSymbol(sprites[i], i));
        m_symbols.back().setSpritePosition({ m_position.x, m_position.y + i * m_spriteSize.y });
    }

    std::shuffle(m_symbols.begin(), m_symbols.end(), random.getEngine());

    for (auto& symbol : m_symbols) {
        m_symbolsPos.push_back(symbol.getId());
    }

    m_spriteSize = m_symbols.front().getSize();
}

void Reel::startSpin() {
    m_isRolling = true;
}

const ReelSymbol& Reel::getCenterSymbol() const {
    size_t index = m_symbolsPos[m_centralSymbolIndex];

    for (auto& symbol : m_symbols) 
        if (symbol.getId() == index) 
            return symbol;

    return m_symbols[index];
}

void Reel::endSpin() {
    m_isRolling = false;
    m_isAligning = true;
    m_alignOffset = caclAlignOffset();
}

void Reel::setPosition(const sf::Vector2f& newPos) {
    m_position = newPos;

    for (size_t i = 0; i < m_symbols.size(); ++i) {
        m_symbols[i].setSpritePosition({
            m_position.x,
            m_position.y + i * m_spriteSize.y
        });
    }
}

void Reel::shiftBy(const int32_t& shift) {
    std::rotate(m_symbolsPos.rbegin(), m_symbolsPos.rbegin() + (shift % m_symbols.size()), m_symbolsPos.rend());
}

bool Reel::isSpinning() const {
    return m_isRolling;
}

bool Reel::isAligning() const {
    return m_isAligning;
}

sf::Vector2i Reel::getSymbolSize() const {
    return m_spriteSize;
}

float Reel::caclAlignOffset() const {

    auto it = std::find(m_symbolsPos.begin(), m_symbolsPos.end(), 0);
    auto index = std::distance(m_symbolsPos.begin(), it);

    sf::Vector2f targetPos{ m_position.x, m_position.y + (float)(index) * (float)m_spriteSize.y };

    sf::Vector2f spritePos = std::find_if(m_symbols.begin(), m_symbols.end(), [](const ReelSymbol& symbol) {
        return symbol.getId() == 0;
    })->getSpritePosition();

    float offset = targetPos.y >= spritePos.y
        ? targetPos.y - spritePos.y
        : (m_spriteSize.y * m_symbols.size()) - spritePos.y + targetPos.y;


    float additionalOffset = m_spriteSize.y * m_symbols.size() * 2 + 1; // Дополнительный оффсет для анимации прокрутки

    return offset + additionalOffset;
}

void Reel::moveAllBy(const float& delta) {
    for (auto& sprite : m_symbols) {
        sprite.moveTo({ 0, delta });

        if (sprite.getSpritePosition().y > m_position.y + m_spriteSize.y * m_symbols.size()) {
            sprite.setSpritePosition({ m_position.x, (sprite.getSpritePosition().y - m_symbols.size() * m_spriteSize.y) });
        }
    }
}

void Reel::update(const float& deltaTime) {
    if (m_isRolling) {
        moveAllBy(m_velocity * deltaTime);
    } 
    else if (m_isAligning && m_alignOffset > 0.01f) {
        float delta = std::min(m_alignOffset, m_velocity * deltaTime);
        moveAllBy(delta);
        m_alignOffset -= delta;

        if (m_alignOffset < 0.01f) {
            m_isAligning = false;
            m_alignOffset = 0.f;
        }
    }
}

void Reel::draw(sf::RenderWindow& window) {
    for (auto& symbol : m_symbols) {
        symbol.draw(window);
    }
}