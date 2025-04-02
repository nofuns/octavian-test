#pragma once

#include "IEntity.hpp"
#include "Reel.hpp"
#include "IGameRule.hpp"
#include "Command.hpp"
#include "SlotMachineState.hpp"
#include "Random.hpp"

class SlotMachine : public IEntity {
public:
    explicit SlotMachine(const std::vector<sf::Sprite>& reelSprites, const size_t& reelsCount, std::unique_ptr<IGameRule> gameRule);
    ~SlotMachine() = default;

    void startReelsRotation();
    void endReelsRotation();

    void setPosition(const sf::Vector2f& newPos);

    bool isAligned() const;
    
    void setState(std::unique_ptr<StateBase> newState);

    int64_t getTotalScore() const;

    int64_t calcScore();

    void handle_input(const Command& cmd);

    void update(const float& deltaTime) override;

    void draw(sf::RenderWindow& window) override;

private:
    std::vector<ReelSymbol> getCentralSymbols() const;

private:
    Random m_random;
    std::unique_ptr<StateBase>  m_state;
    std::vector<Reel>           m_reels;
    sf::Vector2f                m_position;
    std::unique_ptr<IGameRule>  m_scoreCalcRule;

    int64_t m_totalScore;
};