#pragma once 

#include "IEntity.hpp"
#include "ReelSymbol.hpp"

#include <vector>
#include <SFML/Graphics.hpp>

class Random;

class Reel : public IEntity {
public:
    explicit Reel(const std::vector<sf::Sprite>& _sprites, Random& random);

    ~Reel() = default;

    void startSpin();
    void endSpin();

    void shiftBy(const int32_t& shift);

    bool isSpinning() const;
    
    bool isAligning() const;
   
    sf::Vector2i getSymbolSize() const;

    void setPosition(const sf::Vector2f& newPos);

    void update(const float& deltaTime) override;

    void draw(sf::RenderWindow& window) override;

    void moveAllBy(const float& delta);

    const ReelSymbol& getCenterSymbol() const;

private:
    float caclAlignOffset() const;

private:
    sf::Vector2f m_position;
    sf::Vector2i m_spriteSize;

    std::vector<ReelSymbol> m_symbols;
    std::vector<int32_t> m_symbolsPos;
    static constexpr size_t m_centralSymbolIndex = 2;  // Индекс символа из середины отображенной части барабана

    bool m_isRolling;
    bool m_isAligning;

    const float m_velocity;
    float m_alignOffset;
};