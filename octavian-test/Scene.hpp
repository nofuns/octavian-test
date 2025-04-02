#pragma once

#include "IEntity.hpp"

#include <map>
#include <string>
#include <SFML/Graphics.hpp>


class Scene : public IEntity {
public:
	Scene() = default;

	void addEntity(const std::string& name, std::shared_ptr<IEntity> entity);

	void draw(sf::RenderWindow& window) override;

	void update(const float& deltaTime) override;

private:
	std::map<std::string, std::shared_ptr<IEntity> > m_entities;

};
