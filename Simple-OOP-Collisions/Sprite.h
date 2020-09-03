#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL.h>

class Sprite
{
	//Base class for particles 

public: 
	Sprite(SDL_Renderer* _renderer, char* _filename, int _w, int _h);	//constructor
	~Sprite();	//destructor

	void Draw(SDL_Renderer* _renderer, int _x, int _y);	//Draws object
protected:

	SDL_Texture* m_tex; // Texture 
	SDL_Rect m_posRect; // Position & size of object

};
#endif