#include "Scene.hpp"

#include "SFML/Graphics.hpp"


void Scene::addEntity(const std::string& name, std::shared_ptr<IEntity> entity) {
	m_entities[name] = entity;
}

void Scene::draw(sf::RenderWindow& window) {
	for (auto& [name, entity] : m_entities) {
		entity->draw(window);
	}
}

void Scene::update(const float& deltaTime) {
	
	for (auto& [name, entity] : m_entities) {
		entity->update(deltaTime);
	}
}