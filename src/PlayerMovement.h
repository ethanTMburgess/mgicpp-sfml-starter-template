#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <deque>
#include "PlayingState.h"

struct Waypoint;
class PlayingState;
class GameObject;

class PlayerMovement
{
public:
	void replaceWaypoints(const sf::Vector2f& waypoint);
	void Move(float dt);




	PlayingState* playing = nullptr;

	float speed = 100.f;

	std::deque<sf::Vector2f> waypoints;

	

    //sf:Sprite* up_sprite = nullptr;


private:
};