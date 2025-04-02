#include "SlotMachine.hpp"

#include "SlotMachineState.hpp"
#include "Reel.hpp"
#include "IGameRule.hpp"
#include <random>


SlotMachine::SlotMachine(const std::vector<sf::Sprite>& reelSprites, const size_t& reelsCount, std::unique_ptr<IGameRule> gameRule)
    : m_reels(),
    m_state(std::make_unique<WaitingState>()),
    m_position({ 0, 0 }),
    m_totalScore(0),
    m_scoreCalcRule(std::move(gameRule)),
    m_random(0, 20)
{
    m_reels.reserve(reelsCount);
    for (size_t i = 0; i < reelsCount; ++i) {
        m_reels.emplace_back(Reel(reelSprites, m_random));
    }

    setPosition(m_position);

    m_state = std::make_unique<WaitingState>(this);
}

void SlotMachine::setPosition(const sf::Vector2f& newPos) {

    m_position = newPos;
    auto symbolSize = m_reels.front().getSymbolSize();
    for (size_t i = 0; i < m_reels.size(); ++i) {
        m_reels[i].setPosition({i * symbolSize.x + m_position.x, - symbolSize.y + m_position.y });
    }
}

void SlotMachine::handle_input(const Command& cmd) {
    m_state.get()->handle_input(cmd);
}

bool SlotMachine::isAligned() const {
    for (auto& reel : m_reels)
        if (reel.isAligning())
            return false;

    return true;
}

std::vector<ReelSymbol> SlotMachine::getCentralSymbols() const {
    std::vector<ReelSymbol> centerSymbols;
    centerSymbols.reserve(m_reels.size());

    for (auto& reel : m_reels) {
        centerSymbols.push_back(reel.getCenterSymbol());
    }

    return centerSymbols;
}

int64_t SlotMachine::getTotalScore() const {
    return m_totalScore;
}

int64_t SlotMachine::calcScore() {
    m_totalScore += m_scoreCalcRule->calculateScore(getCentralSymbols());
    return m_totalScore;
}

void SlotMachine::startReelsRotation() {
    for (auto& reel : m_reels) {
        reel.shiftBy(m_random.getInt());
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