#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game;
class PlayingState;

class UImanager
{


public:
	UImanager();


	void mouseClicked(sf::RenderWindow& window, sf::Event event);

	void UpdateUI();

	void renderPlayingUI(sf::RenderWindow& window);

	void renderMenuUI(sf::RenderWindow& window);



	// Initialize UI
	bool initPlayingUI();
	bool initdayEndUI();
	bool initMenuUI();

	// Update and render

	

	void setgame(Game* gamePtr) { game = gamePtr; }
	void setPlayingState(PlayingState* playingState) { playing = playingState; }
	int mistakesCounter = 3;
	int getMistakesCounter() const { return mistakesCounter; }


	//sounds
	//sf::SoundBuffer buttonPressBuffer;
	//sf::SoundBuffer stampPressBuffer;
	//sf::Sound buttonPressSound;
	//sf::Sound stampSound;




	// getters and setters for these variables, then move to private
	// UI state
	bool yesButtonDown = false;
	bool noButtonDown = false;
	
	bool yesButtonPressed = false;
	bool noButtonPressed = false;
	bool nextButtonPressed = false;
	
	
	
	



	bool passportValid = false;

	float ButtonTimer = 0.0f;

	const float stampVisible = 407;//windowWidth - stampWidth;
	const float stampHidden = 570;// windowWidth;



	// UI objects
	
	
	GameObject yesButton;
	GameObject noButton;
	GameObject nextButton;

	GameObject playButton;
	GameObject quitButton;
	





private:
	// UI constants
	




	Game* game;
	PlayingState* playing;


};
