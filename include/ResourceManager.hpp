#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>

/**
 * @brief Manages resources to prevent more than one instance any texture/sound/font being used at once.
 * 
 */
class ResourceManager
{
public:
	/**
	 * @brief Get the texture at the given path.
	 * 
	 * @param path The texture's path.
	 * @return sf::Texture* A pointer to that texture.
	 */
	sf::Texture* texture(std::string path);

private:
	/**
	 * @brief A map of textures to their paths.
	 * 
	 */
	std::unordered_map<std::string, sf::Texture> mTextures;
};