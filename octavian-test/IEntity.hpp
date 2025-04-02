#pragma once

namespace sf { class RenderWindow; };

class IEntity {
public:
    virtual void update(const float& deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};

