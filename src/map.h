#pragma once
#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "Layer.h"

class Map
{
public:
    Map() = default;
    Map(int tileSize, int width, int height);

    void AddLayer(Layer layer);

    // Getters
    std::vector<Layer>& getLayers() { return layers; };
    const std::vector<Layer>& getLayers() const { return layers; };

    int getTileSize() const { return tileSize; };
    int getMapWidth() const { return mapWidth; };
    int getMapHeight() const { return mapHeight; };
    std::shared_ptr<sf::Texture>& GetSpriteSheet() { return spritesheet; };
    const std::shared_ptr<sf::Texture>& GetSpriteSheet() const { return spritesheet; };

    // Load sprite sheet from file. Returns true on success.
    bool setSpriteSheet(const std::string& path);

private:
    int tileSize = 0;
    int mapWidth = 0;
    int mapHeight = 0;

    std::vector<Layer> layers;

    std::shared_ptr<sf::Texture> spritesheet;
};