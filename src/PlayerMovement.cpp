#include "PlayerMovement.h"
#include <cmath>
#include "PlayingState.h"
#include "GameObject.h"
#include <iostream>


void PlayerMovement::replaceWaypoints(const sf::Vector2f& waypoint)
{
	waypoints.clear();
	waypoints.push_back(waypoint);
}


void PlayerMovement::Move(float dt)
{
	if (!playing) return;
	if (waypoints.empty()) return;
	
	
	sf::Vector2f playerPos = playing->player.getPlayerPosition();
	sf::Vector2f target = waypoints.front();

	sf::Vector2f  direction{ target.x -  playerPos.x, target.y -  playerPos.y };
	float distance = std::hypot(direction.x,   direction.y);

		if (distance < 1.0f)
		{
			waypoints.pop_front();

		}
		else
		{
			direction.x /=  distance;
			direction.y /= distance;

			float dx = direction.x  * speed * dt;
			float dy  = direction.y * speed  * dt;

			playing->player.move(dx, dy);

			sf::FloatRect playerBounds = playing->player.getSprite()->getGlobalBounds();
			if (playing->handleMapCollisios(playerBounds))
			{
				playing->player.move(-dx, -dy);
			}
		}
	
	
}
