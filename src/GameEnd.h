#pragma once
#include<SFML/Graphics.hpp>
#include "Game.h"

class Game;

class GameEnd
{
public:
	GameEnd(Game* game);
	~GameEnd();

	bool init(bool won);
	void update(float dt);
	void render(sf::RenderWindow& window);
	void MouseClick(const sf::Vector2f& clickPos);


private:
	Game* game;
	sf::Text endText;
	sf::Text playAgainText;
	bool win;

};
