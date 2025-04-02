#include "UI.hpp"

void UserInterface::checkClick(const sf::Vector2i& mousePos) {
	for (auto& [name, button] : m_buttons) {
		button->checkClick(mousePos);
	}
}

void UserInterface::addButton(const std::string& key, std::unique_ptr<Button> button) {
	m_buttons[key] = std::move(button);
}

void UserInterface::addTextField(const std::string& key, std::unique_ptr<TextField> textField) {
	m_textFields[key] = std::move(textField);
}

void UserInterface::updateTextField(const std::string& key, const std::string& text) {
	m_textFields[key]->setText(text);
}

void UserInterface::draw(sf::RenderWindow& window) {
	for (auto& [name, button] : m_buttons) {
		button->draw(window);
	}

	for (auto& [name, textField] : m_textFields) {
		textField->draw(window);
	}
}