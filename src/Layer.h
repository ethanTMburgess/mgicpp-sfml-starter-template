#pragma once
#include <vector>
#include <string>
#include "Tile.h"

class Layer
{
public:
	
	Layer(std::string name, bool collider);

	void addTile(Tile tile);

	//Getters
	std::string& GetName() { return lName; };
	bool HasCollider() const { return hasCollider; };
	std::vector<Tile>& GetTiles() { return tiles; };

	const std::vector <Tile>& GetTiles() const { return tiles; }

private:
	bool hasCollider;
	std::string lName;

	std::vector<Tile> tiles;
};