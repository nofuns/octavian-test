#include "SlotMachineState.hpp"
#include "SlotMachine.hpp"


/////////////////////////////////////////////////

WaitingState::WaitingState(SlotMachine* slotMachine) : StateBase(slotMachine) {
}

void WaitingState::change_state() {
	m_slotMachine->setState(std::make_unique<RollingState>(m_slotMachine));
}

void WaitingState::update() {

}

void WaitingState::handle_input(const Command& cmd) {
	if (cmd == Command::START_ROLLING)
		change_state();
}

/////////////////////////////////////////////////

RollingState::RollingState(SlotMachine* slotMachine) : StateBase(slotMachine) {
	ellapsedTime = clock.restart();
	m_slotMachine->startReelsRotation();
}

void RollingState::change_state() {
	m_slotMachine->endReelsRotation();
	m_slotMachine->setState(std::make_unique<AlignState>(m_slotMachine));
}

void RollingState::update() {
	ellapsedTime += clock.restart();
	if (ellapsedTime.asSeconds() > rollingTime)
		change_state();
}

void RollingState::handle_input(const Command& cmd) {
	if (cmd == Command::END_ROLLING)
		change_state();
}

/////////////////////////////////////////////////


AlignState::AlignState(SlotMachine* slotMachine) : StateBase(slotMachine) {
}

void AlignState::change_state() {
	m_slotMachine->setState(std::make_unique<WinningState>(m_slotMachine));
}

void AlignState::update() {
	if (m_slotMachine->isAligned())
		change_state();
}

void AlignState::handle_input(const Command& cmd) {

}


/////////////////////////////////////////////////

WinningState::WinningState(SlotMachine* slotMachine) : StateBase(slotMachine) {
	m_slotMachine->calcScore();
}

void WinningState::change_state() {
	m_slotMachine->setState(std::make_unique<WaitingState>(m_slotMachine));
}

void WinningState::update() {
	change_state();
}

void WinningState::handle_input(const Command& cmd) {

}