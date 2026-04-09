#pragma once
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "PlayerMovement.h"
#include <memory>

class GameObject;
class UImanager;
class PlayingState;
class MenuState;
class PlayerMovement;
class GameEnd; // forward declare GameEnd

enum class GameState
{
	MENU,
	PLAYING,
	GAMEEND
};

class Game
{


 public:

	 AssetManager assets;
	 AssetManager& getAssets() { return assets; };


  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

  void mouseMoved(sf::Event event);

  void mouseReleased(sf::Event event);

  void mousePressed(sf::Event event);

  bool collisionCheck(const sf::Vector2f& click, GameObject& object);

  void resetPlayingState();

  void mouseButtonPressed(sf::Event event, sf::Vector2f cursor_location);

  PlayerMovement* getPlayerMovement() { return playerMove.get(); }

  GameEnd* getGameEnd() { return EndOfGame.get(); }

  GameState currentState;

  sf::Vector2f worldPos;

  



  // getters
  sf::Font& getFont() { return font; }
  UImanager* getUI() { return UI.get(); }

  //setters
  void setState(GameState newState);

  

 private:

	 std::unique_ptr<UImanager> UI;
	 std::unique_ptr < PlayingState> playing;
	 std::unique_ptr < MenuState> menu;
     std::unique_ptr <PlayerMovement> playerMove;
	 std::unique_ptr <GameEnd> EndOfGame;


  sf::RenderWindow& window;
  sf::Sprite ball;
  sf::Texture ball_texture;

  sf::Font font;

};

#endif // PLATFORMER_GAME_H
