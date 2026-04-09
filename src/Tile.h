#pragma once
#include <SFML/Graphics.hpp>

class Tile {
public:
	Tile(int ID, int X, int Y, std::shared_ptr<sf::Texture> text);

	int getId() const { return id; };
	int getX() const { return x; };
	int getY() const { return y; };
	sf::Sprite& GetSprite() { return *sprite; };

private:

	std::unique_ptr<sf::Sprite> sprite;

	std::shared_ptr<sf::Texture> texture;
	int id;
	int x;
	int y;

};
