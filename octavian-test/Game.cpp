#include "Game.hpp"
#include "Scene.hpp"
#include "SlotMachineState.hpp"
#include "UI.hpp"
#include <memory>

Game::Game()
	: m_window(sf::VideoMode({ 800, 600 }, 32), "Game"), m_scene(nullptr)
{
	m_window.setFramerateLimit(60);
	
	init();
}

void Game::loop() {
    while (m_window.isOpen()) {
		updateScore();
		handleEvents();
		update();
		drawAll();
		display();
    }
}

void Game::handleInput(Command cmd) {
	m_slotMachine->handle_input(cmd);
}

void Game::updateScore() {
	m_ui->updateTextField("totalScore", std::string{ "Total score: " } + std::to_string(m_slotMachine->getTotalScore()));
}

void Game::handleEvents() {
	while (const std::optional event = m_window.pollEvent()) {
		if (event->is<sf::Event::Closed>())
			m_window.close();

		if (event->is<sf::Event::MouseButtonPressed>() && event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
			m_ui->checkClick(event->getIf<sf::Event::MouseButtonPressed>()->position);
	}
}

void Game::init() {
	loadTextures();
	m_slotMachine = createSlotMachine();
	m_slotMachine->setPosition({24, 88});

	m_scene = std::make_unique<Scene>();
	m_scene->addEntity("slotMachine1", m_slotMachine);
	m_ui = std::move(createUI());
}

std::shared_ptr<SlotMachine> Game::createSlotMachine() {
    std::vector<sf::Sprite> reelSprites = { 
		sf::Sprite(*m_texturePool.get("coal")),
		sf::Sprite(*m_texturePool.get("diamond")),
		sf::Sprite(*m_texturePool.get("emerald")),
		sf::Sprite(*m_texturePool.get("pearl")),
		sf::Sprite(*m_texturePool.get("ruby"))
	};


	for (auto& sprite : reelSprites) {
		sprite.setScale({ 3, 3 });
	}

	m_foreground = std::make_unique<sf::Sprite>(*m_texturePool.get("slotMachine"));
	
	return std::make_shared<SlotMachine>(
		reelSprites,
		5,
		std::make_unique<GameRuleMaxConsecutiveElements>());;
}

void Game::loadTextures() {
	m_texturePool.add(
		"coal",
		std::make_shared<sf::Texture>("data/sprites/coal.png", false, sf::IntRect({ 0, 0 }, { 32, 32 })));

	m_texturePool.add(
		"diamond",
		std::make_shared<sf::Texture>("data/sprites/diamond.png", false, sf::IntRect({ 0, 0 }, { 32, 32 }))
	);

	m_texturePool.add(
		"emerald",
		std::make_shared<sf::Texture>("data/sprites/emerald.png", false, sf::IntRect({ 0, 0 }, { 32, 32 }))
	);

	m_texturePool.add(
		"pearl",
		std::make_shared<sf::Texture>("data/sprites/pearl.png", false, sf::IntRect({ 0, 0 }, { 32, 32 }))
	);

	m_texturePool.add(
		"ruby",
		std::make_shared<sf::Texture>("data/sprites/ruby.png", false, sf::IntRect({ 0, 0 }, { 32, 32 }))
	);

	m_texturePool.add(
		"slotMachine",
		std::make_shared<sf::Texture>("data/slot_machine.png", false, sf::IntRect({ 0, 0 }, { 800, 600 }))
	);

	m_texturePool.add(
		"startButton",
		std::make_shared<sf::Texture>("data/start_button.png", false, sf::IntRect({ 0, 0 }, { 64, 32 }))
	);

	m_texturePool.add(
		"stopButton",
		std::make_shared<sf::Texture>("data/stop_button.png", false, sf::IntRect({ 0, 0 }, { 64, 32 }))
	);
}


void Game::update() {
	m_deltaTime = m_deltaClock.restart();
	m_scene->update(m_deltaTime.asSeconds());
}

void Game::drawAll() {
	m_scene->draw(m_window);
	m_window.draw(*m_foreground);
	m_ui->draw(m_window);
}

void Game::display() {
	m_window.clear();

	drawAll();

	m_window.display();
}

std::unique_ptr<UserInterface> Game::createUI() {
	std::unique_ptr<UserInterface> ui = std::make_unique<UserInterface>();

	ui->addButton(
		"startButton",
		std::make_unique<Button>(
			*m_texturePool.get("startButton"),
			"",
			sf::Vector2f{ 600, 150 },
			[this]() {this->handleInput(Command::START_ROLLING); }
		)
	);


	ui->addButton(
		"stopButton",
		std::make_unique<Button>(
			*m_texturePool.get("stopButton"),
			"",
			sf::Vector2f{ 600, 250 },
			[this]() {this->handleInput(Command::END_ROLLING); })
	);

	ui->addTextField(
		"totalScore",
		std::make_unique<TextField>(
			"data/fonts/arial.ttf",
			sf::Vector2f{20, 20}
		)
	);
	
	return ui;
}
