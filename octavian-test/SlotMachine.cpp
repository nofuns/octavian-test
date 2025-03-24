#include "SlotMachine.hpp"

#include "SlotMachineState.hpp"
#include "Reel.hpp"
#include "IGameRule.hpp"
#include <random>


SlotMachine::SlotMachine(std::vector<sf::Sprite> reelSprites, size_t reelsCount, std::unique_ptr<IGameRule> gameRule)
    : m_reels(), m_state(std::make_unique<WaitingState>(this)), m_position({ 0, 0 }), m_totalScore(0), m_scoreCalcRule(std::move(gameRule))
{
    for (size_t i = 0; i < reelsCount; ++i) {
        m_reels.push_back(Reel(reelSprites));
    }


    setPosition(m_position);
}

void SlotMachine::setPosition(const sf::Vector2f& newPos) {

    m_position = newPos;
    auto symbolSize = m_reels.front().getSymbolSize();
    for (size_t i = 0; i < m_reels.size(); ++i) {
        m_reels[i].setPosition({i * symbolSize.x + m_position.x, - symbolSize.y + m_position.y });
    }
}

void SlotMachine::handle_input(Command cmd) {
    m_state.get()->handle_input(cmd);
}

bool SlotMachine::isAligned() const {
    for (auto& reel : m_reels)
        if (reel.isAligning())
            return false;

    return true;
}

std::vector<ReelSymbol> SlotMachine::getCentralSymbols() {
    std::vector<ReelSymbol> centerSymbols;
    centerSymbols.reserve(m_reels.size());

    for (auto& reel : m_reels) {
        centerSymbols.push_back(reel.getCenterSymbol());
    }

    return centerSymbols;
}

int32_t SlotMachine::getTotalScore() const {
    return m_totalScore;
}

int32_t SlotMachine::calcScore() {
    m_totalScore += m_scoreCalcRule->calculateScore(getCentralSymbols());
    return m_totalScore;
}

void SlotMachine::startReelsRotation() {

    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> dist(1, 20);

    for (auto& reel : m_reels) {
        reel.shiftBy(dist(gen));
        reel.startSpin();
    }
}

void SlotMachine::endReelsRotation() {
    for (auto& reel : m_reels) {
        reel.endSpin();
    }
}

void SlotMachine::setState(std::unique_ptr<StateBase> newState) {
    m_state = std::move(newState);
}

void SlotMachine::update(const float& deltaTime) {
    m_state.get()->update();
    for (auto& reel : m_reels) {
        reel.update(deltaTime);
    }
}

void SlotMachine::draw(sf::RenderWindow& window) {
    for (auto& reel : m_reels) {
        reel.draw(window);
    }
}