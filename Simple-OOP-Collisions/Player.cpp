#include "Player.h"

// constructor function (see comments in Player.h and Main.cpp GameLoop function)
Player::Player(SDL_Renderer* renderer, char* filename, int w, int h)
{
	// start these pointers off as NULL...
	playerSprite = NULL;
	controller = NULL;

	//...now try to overwrite them with their proper values
	playerSprite = new Sprite(renderer, "spaceship.bmp", w, h); // new Sprite object
	controller = SDL_GameControllerOpen(0); // try to connect to controller 0 (the first player pad)

	// if either of the above failed then the pointer will still be NULL

	// some initial values for these
	posX = 500;
	posY = 500;
	speed = 5;
	boost = 1;
}

// destructor function (see comment in Player.h and GameLoop function in Main.cpp)
Player::~Player()
{
	// if we sucessfully created a Sprite object then delete it
	if (playerSprite != NULL)
	{
		delete playerSprite;
	}

	// if we opened a controller connection then close it
	if (controller != NULL)
	{
		SDL_GameControllerClose(controller);
	}
}

/* an update function will typically be called once per frame,
   which we do from the GameLoop function in Main.cpp */
void Player::Update()
{
	// other functions in this file
	HandleKeyboard();
	HandleController();
}

// draw the Player
void Player::Draw(SDL_Renderer* renderer)
{
	/* if we successfully created a Sprite object then call
	   its Draw function */
	if (playerSprite != NULL)
	{
		playerSprite->Draw(renderer, posX, posY);
	}
}

void Player::HandleKeyboard()
{
	/* get a pointer to SDLs internal array which represents the state of
	   all the keys on the keyboard */
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	// if left shift is down then make boost higher
	if (keyboardState[SDL_SCANCODE_LSHIFT])
	{
		boost = 5;
	}
	else
	{
		boost = 1;
	}

	/* the below 4 if-statements just change the values of
	   posX & posY depending on the arrow keys being pressed */

	if (keyboardState[SDL_SCANCODE_RIGHT]) 
	{
		posX += speed * boost;
	}

	if (keyboardState[SDL_SCANCODE_LEFT]) 
	{
		posX -= speed * boost;
	}

	if (keyboardState[SDL_SCANCODE_DOWN])
	{
		posY += speed * boost;
	}

	if (keyboardState[SDL_SCANCODE_UP])
	{
		posY -= speed * boost;
	}
}

void Player::HandleController()
{
	// if we did not connect to a controller then just return from this function
	// we tried connecting in the constructor function (top of this file)
	if (controller == NULL) 
	{
		return;
	}

	// if 'A' button is down then make boost higher
	if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A))
	{
		boost = 5;
	}
	else
	{
		boost = 1;
	}

	// read the left sticks X & Y values, these will be -32767 to +32768
	float leftStickX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
	float leftStickY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);

	// divide both by 32768 to make them be in range -1.0 to +1.0
	leftStickX /= 32768.0f;
	leftStickY /= 32768.0f;

	/* the below if-statements change posX & posY depending on how the
	   left stick values are. The reason we only consider values outside
	   of -0.2 to +0.2 is because this ignores the slight off center position
	   of a stick that is not being used. This is called the sticks deadzone. */

	if (leftStickX < -0.2f || leftStickX > 0.2f)
	{
		posX += leftStickX * speed * boost;
	}

	if (leftStickY < -0.2f || leftStickY > 0.2f)
	{
		posY += leftStickY * speed * boost;
	}
}