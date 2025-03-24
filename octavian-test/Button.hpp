#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    Button(const sf::Texture& texture, std::string text, sf::Vector2f location, std::function<void()> callback)
        : m_sprite(texture), m_onClickCallback(callback)
    {
        m_sprite.setPosition(location);
        m_text = text;
    }

    void checkClick(const sf::Vector2i& mousePos) {
        if (mousePos.x > m_sprite.getPosition().x
            && mousePos.x < (m_sprite.getPosition().x + m_sprite.getTextureRect().size.x))
        {
            if (mousePos.y > m_sprite.getPosition().y
                && mousePos.y < (m_sprite.getPosition().y + m_sprite.getTextureRect().size.y))
            {
                onClick();
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(m_sprite);
    }

private:
    void onClick() {
        m_onClickCallback();
    }

private:
    sf::Sprite  m_sprite;
    std::string m_text;

    std::function<void()> m_onClickCallback;
};