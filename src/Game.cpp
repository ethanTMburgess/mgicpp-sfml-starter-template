#include "Game.h"
#include "GameObject.h"
#include "UImanager.h"
#include "PlayingState.h"
#include "MenuState.h"
#include "JsonLoader.h"
#include "map.h"
#include "GameEnd.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{

	UI = std::make_unique<UImanager>();
	UI->setgame(this);          
	UI->initMenuUI();

	if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
	{
		std::cerr << "Failed to load font!" << std::endl;
		return false;
	}

	playerMove = std::make_unique<PlayerMovement>();

	playing = std::make_unique<PlayingState>(this);

	menu = std::make_unique<MenuState>(this);

	EndOfGame = std::make_unique<GameEnd>(this);
	

	if (playing)
	{
		if (!playing->init())
		{
			std::cerr << "ERROR initializing playing state" << std::endl;
			return false; 
		}
	}

	if (playerMove && playing)
	{
		playerMove->playing = playing.get();
	}

	currentState = GameState::MENU;


  return true;
}

void Game::update(float dt)
{
	switch (currentState)
	{
	case GameState::MENU:
		menu->update(dt);
		break;

	case GameState::PLAYING:
		playing->update(dt);
		break;
	
	case GameState::GAMEEND:
		EndOfGame->update(dt);
		break;

	
	}
}

void Game::render()
{
	switch (currentState)
	{

		// if game is in menu state
	case GameState::MENU:
		UI->renderMenuUI(window);
		menu->init();
		menu->render(window);
		break;

		// if game is in playing state
	case GameState::PLAYING:
		playing->render(window);
		UI->renderPlayingUI(window);
		break;

	case GameState::GAMEEND:
		EndOfGame->render(window);
		break;
	}
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

//void Game::keyPressed(sf::Event event)
//{

//}

void Game::mouseMoved(sf::Event event)
{

	


}

void Game::mouseReleased(sf::Event event)
{

	
	return;



}

void Game::mousePressed(sf::Event event)
{
	sf::Vector2i pixelClick{ event.mouseButton.x, event.mouseButton.y };
	sf::Vector2f worldClick = window.mapPixelToCoords(pixelClick);

	if (currentState == GameState::GAMEEND)
	{
		EndOfGame->MouseClick(worldClick);
	}

	if (UI)
	{
		UI->mouseClicked(window, event);
	}

	



}

bool Game::collisionCheck(const sf::Vector2f& click, GameObject& object)
{

	sf::Sprite* sprite = object.getSprite();

	if (!sprite)
	{
		
		return false;
	}

	
	const sf::Texture* texture = sprite->getTexture();


	

	try
	{
		sf::FloatRect bounds = sprite->getGlobalBounds();
		return bounds.contains(click.x, click.y);
	}
	catch (...)
	{
		
		return false;
	}
}

void Game::resetPlayingState()
{

	playing.reset();


	playing = std::make_unique<PlayingState>(this);
	playing->init();
	if (playerMove)
	{
		playerMove->playing = playing.get();
	}

	if (UI) {
		UI->setPlayingState(playing.get());
	}
}

void Game::mouseButtonPressed(sf::Event event, sf::Vector2f cursor_location)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		if (currentState == GameState::PLAYING && playing) 
		{

			worldPos = window.mapPixelToCoords(
				sf::Vector2i(static_cast<int>(cursor_location.x),
					static_cast<int>(cursor_location.y))
			);
		}
		// playerMove->replaceWaypoints(cursor_location);
		playing->handleClick(worldPos);
	}
}

void Game::setState(GameState newState)
{
	
	if (newState == GameState::PLAYING &&
		(currentState == GameState::MENU || currentState == GameState::GAMEEND))
	{
		resetPlayingState();
	}
	
	currentState = newState;
}


