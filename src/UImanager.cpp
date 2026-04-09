#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>

#include <Windows.h>
#include <cmath>

#include "Game.h"
#include "GameObject.h"
#include "Vector2.h"
#include "UImanager.h"
#include "PlayingState.h"



UImanager::UImanager()
{


	playing = nullptr;
	game = nullptr;



}




bool UImanager::initPlayingUI()
{

	yesButton.getImageFromPath("../Data/Images/GeneralAssets/yes button.png");
	yesButton.setPosition(160, 200);

	noButton.getImageFromPath("../Data/Images/GeneralAssets/no button.png");
	noButton.setPosition(yesButton.sprite.getPosition().x, yesButton.sprite.getPosition().y + 300);









	return true;
}










bool UImanager::initMenuUI()
{
	playButton.getImageFromPath("../Data/Images/GeneralAssets/yes button.png");
	playButton.setPosition(160, 200);

	quitButton.getImageFromPath("../Data/Images/GeneralAssets/no button.png");
	quitButton.setPosition(playButton.sprite.getPosition().x + 200, playButton.sprite.getPosition().y);

	return true;
}


void UImanager::mouseClicked(sf::RenderWindow& window, sf::Event event)
{

	sf::Vector2i pixelClick{ event.mouseButton.x, event.mouseButton.y };
	sf::Vector2f worldClick = window.mapPixelToCoords(pixelClick);

	if (!game)
	{
		std::cout << "UImanager: game is null!" << std::endl;
		return;
	}

	if (!playing)
	{
		std::cout << "UImanager: playing is null!" << std::endl;
		return;
	}

	if (game->currentState == GameState::MENU)
	{
		if (game->collisionCheck(worldClick, yesButton))
		{
			yesButton.getImageFromPath("../Data/Images/GeneralAssets/yes button pressed.png");
			ButtonTimer = 0.0f;
			game->setState(GameState::PLAYING);
		}

		if (game->collisionCheck(worldClick, noButton))
		{
			noButton.getImageFromPath("../Data/Images/GeneralAssets/no button pressed.png");
			std::cout << "no button pressed\n";
			ButtonTimer = 0.0f;
			exit(0);
			
		}
	}


	

	if (game->currentState == GameState::PLAYING)
	{



		

	




	}

	

	if (game->currentState == GameState::MENU)
	{
		if (game->collisionCheck(worldClick, playButton))
		{
			playButton.getImageFromPath("../Data/assets/crossing/UI/yes button pressed.png");
			ButtonTimer = 0.0f;
			game->currentState = GameState::PLAYING;
		}

		if (game->collisionCheck(worldClick, quitButton))
		{
			std::cout << "quit button pressed\n";
			playButton.getImageFromPath("../Data/assets/crossing/UI/no button pressed.png");
			ButtonTimer = 0.0f;
			exit(0);
		}
	}
}

void UImanager::UpdateUI()
{
	
}

void UImanager::renderPlayingUI(sf::RenderWindow& window)
{
	
}



void UImanager::renderMenuUI(sf::RenderWindow& window)
{
	playButton.render(window);
	quitButton.render(window);
}
