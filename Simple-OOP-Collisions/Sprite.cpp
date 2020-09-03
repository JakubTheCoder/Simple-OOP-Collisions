#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* _renderer, char* _filename, int _w, int _h)
{
	SDL_Surface* imageFile = SDL_LoadBMP(_filename);	//create surface

	m_tex = NULL;	//sets texture to null at first, gets set later

	if (imageFile != NULL)	//if image file is not null == if image file exists
	{
		m_tex = SDL_CreateTextureFromSurface(_renderer, imageFile);	//create texture from surface
	}

	if (imageFile != NULL)	//texture was created, can delete surface
	{
		SDL_FreeSurface(imageFile);
	}

	m_posRect.w = _w;
	m_posRect.h = _h;
}

Sprite::~Sprite()
{

	SDL_DestroyTexture(m_tex);
}

void Sprite::Draw(SDL_Renderer* renderer, int x, int y)
{
	//Sets position of object, to draw it 
	m_posRect.x = x;
	m_posRect.y = y;

	//Draws object if texture is not null
	if (m_tex != NULL)
	{
		SDL_RenderCopy(renderer, m_tex, NULL, &m_posRect);
	}
}