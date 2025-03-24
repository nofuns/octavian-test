#pragma once

#include "SlotMachineState.hpp"
#include "SlotMachine.hpp"
#include "IGameRule.hpp"
#include "Command.hpp"
#include "UI.hpp"
#include "Scene.hpp"
#include "TexturePool.hpp"

class Game final {
public:
	explicit Game();

	void init();

	void loop();

	void handleEvents();
	void update();
	void display();

private:
	void loadTextures();

	void handleInput(Command cmd);

	void updateScore();

	std::shared_ptr<SlotMachine> createSlotMachine();

	std::unique_ptr<UserInterface> createUI();

	void drawAll();

private:
	sf::RenderWindow m_window;
	sf::Clock m_deltaClock;
	sf::Time m_deltaTime;

	std::unique_ptr<sf::Sprite> m_foreground;

	TexturePool m_texturePool;

	std::shared_ptr<SlotMachine>	m_slotMachine;

	std::unique_ptr<Scene>			m_scene;
	std::unique_ptr<UserInterface>	m_ui;
};
