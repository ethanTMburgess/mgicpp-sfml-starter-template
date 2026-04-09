#include "Layer.h"

Layer::Layer(std::string name, bool collider) : lName(name), hasCollider(collider)
{

}

void Layer::addTile(Tile tile)
{
	tiles.push_back(std::move(tile));
}