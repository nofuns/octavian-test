#pragma once 

#include <iostream>
#include <SFML/Graphics.hpp>
#include "IEntity.hpp"

class ReelSymbol : public IEntity {
public:
	ReelSymbol(sf::Sprite sprite, size_t id)
		: m_sprite(sprite), m_id(id)
	{}

	void moveTo(const sf::Vector2f offset) {
		m_sprite.move(offset);
	}

	void setSpritePosition(const sf::Vector2f offset) {
		m_sprite.setPosition(offset);
	}

	sf::Vector2f getSpritePosition() const {
		return m_sprite.getPosition();
	}

	sf::Vector2i getSize() const {

		int width = static_cast<int>(
			std::floor(m_sprite.getTextureRect().size.x * m_sprite.getScale().x));
		int height = static_cast<int>(
			std::floor(m_sprite.getTextureRect().size.y * m_sprite.getScale().y));	

		return { width, height };

	}

	size_t getId() const {
		return m_id;
	}

	void update(const float& deltaTime) {
		
	}

	void draw(sf::RenderWindow& window) override {
		window.draw(m_sprite);
	}

private:
	size_t m_id;
	sf::Sprite m_sprite;
};