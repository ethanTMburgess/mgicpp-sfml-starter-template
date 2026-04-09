#include "Tile.h"

Tile::Tile(int ID, int X, int Y, std::shared_ptr<sf::Texture> tex) : id(ID), x(X), y(Y)
{
	texture = std::make_shared<sf::Texture>();
	texture = tex;

	sprite = std::make_unique<sf::Sprite>();
	sprite->setTexture(*texture);
}