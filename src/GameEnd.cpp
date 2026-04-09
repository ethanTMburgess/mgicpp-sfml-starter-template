#include "GameEnd.h"
#include "Game.h"
#include <iostream>

GameEnd::GameEnd(Game* game) : game(game) {}
GameEnd::~GameEnd() {}

bool GameEnd::init(bool won)
{

	win = won;


	sf::Font& font = game->getFont();

	endText.setFont(font);
	endText.setCharacterSize(30);
	endText.setFillColor(sf::Color::White);
	endText.setPosition(120, 100);

	if (win)
	{
		endText.setString("    Woah! \n   you got all of the coins!!");
		
	}
	else
	{
		endText.setString("     Oh no! \n   You ran out of time!!");
	}


	playAgainText.setFont(font);
	playAgainText.setCharacterSize(30);
	playAgainText.setFillColor(sf::Color::White);
	playAgainText.setString("     click mouse button to \n     return to menu");
	playAgainText.setPosition(80, 240);

	return true;
}

void GameEnd::update(float dt) {

}

void GameEnd::render(sf::RenderWindow& window)
{
	window.draw(endText);
	window.draw(playAgainText);
}

void GameEnd::MouseClick(const sf::Vector2f& clickPos)
{
	game->setState(GameState::MENU);
}