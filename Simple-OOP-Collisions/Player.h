#pragma once

#include <SDL.h>
#include "Sprite.h"

class Player // start of declaration of Player class
{

/* public stuff can be accessed from outside of this class,
   i.e. we can call these functions from the GameLoop function in Main.cpp */
public:

	/* function with same name as the class is a constructor function
	it is called when we make a new object of this class (in Main.cpp) */
	Player(SDL_Renderer* renderer, char* filename, int w, int h);

	/* function with same name as the class preceeded by a '~' is a destructor
	function, it is called when we delete an object of this class,
	this happens at the end of GameLoop in Main.cpp */
	~Player();

	void Update();
	void Draw(SDL_Renderer* renderer);

/* private stuff can only be accessed by code that is part of this class
   this will all be in Player.cpp */
private:

	// these two will be called from Update() (see Player.cpp)
	void HandleKeyboard();
	void HandleController();

	Sprite* playerSprite;				// A Sprite object for Player to use
	SDL_GameController* controller;		// used to try to connect to a controller
	float posX;		// screen X position
	float posY;		// screen Y position
	float speed;	// base movement speed
	float boost;	// boost speed multiplier

}; // end of declaration of Player class