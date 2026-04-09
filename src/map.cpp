#include "map.h"

Map::Map(int tileSize, int width, int height)
    : tileSize(tileSize)
    , mapWidth(width)
    , mapHeight(height)
{
    
    spritesheet = std::make_shared<sf::Texture>();
}

void Map::AddLayer(Layer layer)
{
    layers.push_back(std::move(layer));
}

bool Map::setSpriteSheet(const std::string& path)
{
    if (!spritesheet)
        spritesheet = std::make_shared<sf::Texture>();
    return spritesheet->loadFromFile(path);
}