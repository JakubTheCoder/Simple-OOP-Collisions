#pragma once
#ifndef _TEXT_H_
#define _TEXT_H_

#include <SDL.h>
#include<SDL_ttf.h>
#include <string>

class Text
{
	//Base class for text
public:
	Text(int _x, int _y);	//constructor
	~Text();	//deconstructor

	bool LoadText(SDL_Renderer* _renderer, std::string _text, SDL_Color _color);	//load the text 
	void Draw(SDL_Renderer* _renderer, int _x, int _y);	//Draw

protected:
	TTF_Font* m_font = NULL;	//Font used for text
	SDL_Texture* m_texture;	//texture of text
	SDL_Rect* m_rect;	//position and size
};
#endif // _TEXT_H_
