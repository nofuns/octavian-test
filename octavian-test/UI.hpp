#pragma once

#include "Button.hpp"
#include "TextField.hpp"

#include <map>
#include <SFML/Graphics.hpp>


class UserInterface {
private:
    std::map<std::string, std::unique_ptr<Button> >     m_buttons;
    std::map<std::string, std::unique_ptr<TextField> >  m_textFields;

public:
    UserInterface() = default;
    ~UserInterface() = default;

    void checkClick(const sf::Vector2i& mousePos);

    void addButton(const std::string& key, std::unique_ptr<Button> button);

    void addTextField(const std::string& key, std::unique_ptr<TextField> textField);

    void updateTextField(const std::string& key, const std::string& text);

    void draw(sf::RenderWindow& window);
};