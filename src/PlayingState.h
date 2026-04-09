#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <memory>
#include"GameObject.h"
#include "AssetManager.h"
#include "PlayerMovement.h"

class Game;
class UImanager;
class Map;

class PlayingState
{
public:

    AssetManager assets;
    AssetManager& getAssets() { return assets; };
    PlayingState(Game* game);
    ~PlayingState();

    bool init();
    void update(float dt);
    void render(sf::RenderWindow& window);

    //setting sprite rect
    sf::IntRect getRectForTileId(int id);

    void handleClick(const sf::Vector2f& clickPosition);

    void updateTimerShown();
    void resetGame();
    bool handleCoinCollision();

    bool gameEnded = false;

    sf::Clock gameTimer;
    bool timerRunOut = false;
    float timeLimit = 45.f;
    float seconds = 0.f;
    sf::Text timerText;

    bool handleMapCollisios(const sf::FloatRect& playerBounds) const;

    GameObject player;
    GameObject skeleton;
    // GameObject coin;

    std::vector<GameObject> coinsVector;

private:
    sf::Sprite background;
    Game* game;
    UImanager* UI;
    std::unique_ptr<Map> map;

    //GameObjects

    
   
};