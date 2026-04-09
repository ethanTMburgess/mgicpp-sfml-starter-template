#include "AssetManager.h"

void AssetManager::loadTexture(const std::string& name, const std::string& filename)
{
	sf::Texture texture;
	if (!texture.loadFromFile(filename))
	{
		throw std::runtime_error("failed to load texture: " + filename);
	}

	textures[name] = texture;
}

sf::Texture& AssetManager::getTexture(const std::string& name)
{
	return textures.at(name);
}

void AssetManager::loadFont(const std::string& name, const std::string& filename)
{
	sf::Font font;

	if (!font.loadFromFile(filename))
	{
		throw std::runtime_error("failed to load font: " + filename);
	}

	fonts[name] = font;
}

sf::Font& AssetManager::getFont(const std::string& name)
{
	return fonts.at(name);
}
