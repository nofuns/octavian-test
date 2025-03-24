#pragma once 

#include <map>
#include <SFML/Graphics.hpp>

class TexturePool {
public:
	TexturePool() = default;

	void add(const std::string& key, std::shared_ptr<sf::Texture> texture);
	std::shared_ptr<sf::Texture> get(const std::string& key) const;

private:
	std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;
};