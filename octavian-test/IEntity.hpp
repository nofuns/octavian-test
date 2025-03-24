#pragma once

namespace sf { class RenderWindow; };

class IEntity {
public:
    //virtual void handle_input(sf::Event event) = 0;
    virtual void update(const float& deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};

