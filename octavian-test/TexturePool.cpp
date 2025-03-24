#include "TexturePool.hpp"

#include <iostream>

std::shared_ptr<sf::Texture> TexturePool::get(const std::string& key) const {
	return m_textures.at(key);
}

void TexturePool::add(const std::string& key, std::shared_ptr<sf::Texture> texture) {
	m_textures.insert({key, texture});
}