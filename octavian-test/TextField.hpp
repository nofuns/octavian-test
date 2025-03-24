#pragma once

#include <SFML/Graphics.hpp>

class TextField {
private:
	std::unique_ptr<sf::Text> m_text;
	sf::Font* m_font;
	uint32_t m_charSize;

	sf::Vector2f m_position;	

public:
	TextField() = delete;

	explicit TextField(std::string fontPath, sf::Vector2f position, std::string text = "", uint32_t charSize = 50)
		: m_position(position)
	{
		m_font = new sf::Font(fontPath);

		m_text = std::make_unique<sf::Text>(*m_font, text, charSize);
		m_text->setStyle(sf::Text::Bold);
		m_text->setPosition(m_position);
	}

	void setText(const std::string& text) {
		m_text.get()->setString(text);
	}

	void setPosition(const sf::Vector2f& newPos) {
		m_text.get()->setPosition(newPos);
	}

	void draw(sf::RenderWindow& window) {
		window.draw(*m_text);
	}
};
