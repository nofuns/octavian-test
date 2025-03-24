#pragma once

#include "SFML/Window/Event.hpp"
#include "SFML/Window.hpp"
#include "Command.hpp"

class SlotMachine;

class StateBase {
protected:
	SlotMachine* m_slotMachine = nullptr;

public:
	StateBase() = default;
	explicit StateBase(SlotMachine* slotMachine) : m_slotMachine(slotMachine)
	{}

	virtual void change_state() = 0;
	virtual void update() = 0;
	virtual void handle_input(Command cmd) = 0;
};

class WaitingState : public StateBase {
public:
	WaitingState() = default;

	explicit WaitingState(SlotMachine* slotMachine);

	void change_state() override;

	void update() override;

	void handle_input(Command cmd) override;
};

class RollingState : public StateBase {
private:
	sf::Clock clock;
	sf::Time ellapsedTime;
	float rollingTime = 10.0f;

public:
	RollingState() = default;

	explicit RollingState(SlotMachine* slotMachine);

	void change_state() override;

	void update() override;

	void handle_input(Command cmd) override;
};

class AlignState : public StateBase {
private:
	sf::Clock clock;
	sf::Time ellapsedTime;
	float rollingTime = 10.0f;

public:
	AlignState() = delete;

	explicit AlignState(SlotMachine* slotMachine);

	void change_state() override;

	void update() override;

	void handle_input(Command cmd) override;
};

class WinningState : public StateBase {
public:
	WinningState() = default;

	explicit WinningState(SlotMachine* slotMachine);

	void change_state() override;

	void update() override;

	void handle_input(Command cmd) override;
};
