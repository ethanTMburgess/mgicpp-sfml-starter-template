#include "PlayingState.h"
#include "GameObject.h"
#include "Game.h"
#include "UImanager.h"
#include "map.h"
#include "JsonLoader.h"
#include "PlayerMovement.h"
#include "GameEnd.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include <ranges>
PlayingState::PlayingState(Game* game) : game(game)
, UI(game->getUI())

{
	srand(time(NULL));


	/*
	if (game->getPlayerMovement())
	{
		game->getPlayerMovement()->playing = this;
	}
	*/

	if (UI) UI->setPlayingState(this);

	// std::cout << "playingState CONSTRUCTED AT: " << this << std::endl;

}
PlayingState::~PlayingState()
{
	// std::cout << "playingState DESTROYED AT: " << this << std::endl;
}


bool PlayingState::init()
{

	gameEnded = false;
	//Json stuff
	try
	{
		map = std::make_unique<Map>(JsonLoader::LoadMapFromJson("../../../../Data/map1.json"));
	}
	catch (const std::exception& ex)
	{
		std::cerr << "PlayingState::init failed: " << ex.what() << std::endl;
		return false;
	}

	// Initialize text objects with font from Game
	sf::Font& font = game->getFont();
	font.setSmooth(false);

	/*
	// set up coin vector with positions                 positions
	float x, float y;
	std::vector<sf::Vector2f> coinSet = { {x,y}, {x,y}, {x,y}, {x,y},
		{x,y}, {x,y}, {x,y}, {x,y}, {x,y}, {x,y} };
	for (auto pos : coinSet)
	{
		// random num for each pos of eah coin
		x = rand() % 592;
		y = rand() % 352;
		// dec for GO coin per member
		GameObject coin;
		coin.getImageFromPath("../Data/TDassets/coin.png");
		coin.setPosition(pos.x, pos.y);
		coinsVector.push_back(coin);
	}
	*/



	timerText.setFont(font);
	timerText.setCharacterSize(18);
	timerText.setFillColor(sf::Color::Black);
	timerText.setPosition(1, 1);

	gameTimer.restart();

	timeLimit = 45.f;
	timerRunOut = false;

	updateTimerShown();


	int coinsPlaced = 0;
	while(coinsPlaced < 20)
	{
		float x = rand() % 592;
		float y = rand() % 352;

		GameObject coin;
		coin.getImageFromPath("../Data/TDassets/coin.png");
		coin.setPosition(x, y);

		int tileSize = map->getTileSize();
		bool intersectsCollider = false;


		///// Check if coin intersects with any collidable tile
		for (const auto& layer : map->getLayers())
		{
			if (!layer.HasCollider()) continue;

			for (const auto& tile : layer.GetTiles())
			{
				sf::FloatRect tileBounds(
					tile.getX() * tileSize,
					tile.getY() * tileSize,
					tileSize, tileSize);

				if (coin.getSprite()->getGlobalBounds().intersects(tileBounds))
				{
					std::cout << "Coin spawned on collider, respawning..." << std::endl;
					intersectsCollider = true;
				}
			}
			if (intersectsCollider) break;
		}

		if (!intersectsCollider)
		{
			coinsVector.push_back(coin);
			coinsPlaced++;
		}
		
	}
	
	// Set up player GameObject
	player.getImageFromPath("../Data/TDassets/16 wizard.png");
	player.setPosition(50, 50);

	return true;
}


void PlayingState::update(float dt)
{
	
	if (game->getPlayerMovement())
	{
		
		game->getPlayerMovement()->Move(dt);
	}

	

	handleCoinCollision();

	if (coinsVector.empty())
	{
		game->getGameEnd()->init(true);
		game->setState(GameState::GAMEEND);
		return;
	}

	if (coinsVector.empty())
	{
		game->getGameEnd()->init(true);
		game->setState(GameState::GAMEEND);
		return;
	}

	if (!timerRunOut)
	{
		seconds = gameTimer.getElapsedTime().asSeconds();
		updateTimerShown();


		timeLimit = 45.f - seconds;
		

		if (timeLimit <= 0.f)
		{
			timeLimit = 0.f;
			timerRunOut = true;
			std::cout << "Time's up!" << std::endl;

			game->getGameEnd()->init(false);
			game->setState(GameState::GAMEEND);

			return;
		}
		updateTimerShown();
	}
	
	if (!gameEnded && coinsVector.empty())
	{
		gameEnded = true;
		game->getGameEnd()->init(true);
		game->setState(GameState::GAMEEND);
		return;
	}

	if (!gameEnded && !timerRunOut && timeLimit <= 0.f)
	{
		gameEnded = true;
		game->getGameEnd()->init(false);
		game->setState(GameState::GAMEEND);
		return;
	}

};



void PlayingState::render(sf::RenderWindow& window)
{


	for (Layer& layer : std::views::reverse(map->getLayers()))
	{
		for (Tile& tile : layer.GetTiles())
		{
			tile.GetSprite().setTextureRect(getRectForTileId(tile.getId()));

			tile.GetSprite().setPosition(
				tile.getX() * map->getTileSize(),
				tile.getY() * map->getTileSize()
			);

			window.draw(tile.GetSprite());
		}
	}


	player.render(window);

	for (auto& coin : coinsVector)
	{
		coin.render(window);
	}
	
	window.draw(timerText);
}

sf::IntRect PlayingState::getRectForTileId(int id)
{
	int tileSize = map->getTileSize();
	sf::IntRect rect;

	int tilesPerRow = map->GetSpriteSheet()->getSize().x / tileSize;

	int row = id / tilesPerRow;
	int collum = id % tilesPerRow;

	rect.height = tileSize;
	rect.width = tileSize;
	rect.left = collum * tileSize;
	rect.top = row * tileSize;

	return rect;

}

void PlayingState::handleClick(const sf::Vector2f& clickPosition)
{
	if (game->getPlayerMovement())
	{
		std::cout << "Handling click at position: (" << clickPosition.x << ", " << clickPosition.y << ")" << std::endl;
		game->getPlayerMovement()->replaceWaypoints(clickPosition);
	}
}

bool PlayingState::handleCoinCollision()
{

	/*
	// all edges of player
	float playerPosR = player.getSprite()->getPosition().x + 16;
	float playerPosL = player.getSprite()->getPosition().x;

	float playerPosT = player.getSprite()->getPosition().y;
	float playerPosB = player.getSprite()->getPosition().y + 16;


	// all edges of coins
	float coinPosR = player.getSprite()->getPosition().x + 16;
	float coinPosL = player.getSprite()->getPosition().x;

	float coinPosT = player.getSprite()->getPosition().y;
	float coinPosB = player.getSprite()->getPosition().y + 16;
	*/

	bool collectedCoin = false;
	for (auto it = coinsVector.begin(); it != coinsVector.end();) {
		if (player.getSprite()->getGlobalBounds().intersects(it->getSprite()->getGlobalBounds()))

		{
			it = coinsVector.erase(it);
			std::cout << "collected!" << std::endl;
			collectedCoin = true;
		}

		else
		{
			++it;
		}
	}

	return collectedCoin;
}

bool PlayingState::handleMapCollisios(const sf::FloatRect& playerBounds) const
{
    if (!map) return false;

    int tileSize = map->getTileSize();

    for (const auto& layer : map->getLayers())
    {
        if (!layer.HasCollider()) continue;

        for (const auto& tile : layer.GetTiles())
        {
            sf::FloatRect tileBounds(
                tile.getX() * tileSize,
                tile.getY() * tileSize,
                tileSize, tileSize);

            if (playerBounds.intersects(tileBounds))
            {
                return true;
            }
        }
    }
    return false;
}


void PlayingState::updateTimerShown()
{
	int remaining = static_cast<int>(timeLimit);
	int seconds = remaining % 60;

	std::string timerString = std::to_string(seconds);

	timerText.setString(timerString);
	
}


void PlayingState::resetGame()
{
	gameEnded = false;

	coinsVector.clear();

	gameTimer.restart();
	timeLimit = 45.f;
	timerRunOut = false;
	seconds = 0.f;
	updateTimerShown();


	int coinsPlaced = 0;
	while (coinsPlaced < 20)
	{
		float x = rand() % 592;
		float y = rand() % 352;

		GameObject coin;
		coin.getImageFromPath("../Data/TDassets/coin.png");
		coin.setPosition(x, y);

		int tileSize = map->getTileSize();
		bool intersectsCollider = false;

		for (const auto& layer : map->getLayers())
		{
			if (!layer.HasCollider()) continue;
			for (const auto& tile : layer.GetTiles())
			{
				sf::FloatRect tileBounds(
					tile.getX() * tileSize,
					tile.getY() * tileSize,
					tileSize, tileSize);

				if (coin.getSprite()->getGlobalBounds().intersects(tileBounds))
				{
					intersectsCollider = true;
					break;
				}
			}
			if (intersectsCollider) break;
		}

		if (!intersectsCollider)
		{
			coinsVector.push_back(coin);
			coinsPlaced++;
		}
	}

	player.setPosition(50, 50);
	if (game->getPlayerMovement()) game->getPlayerMovement()->waypoints.clear();
}



















