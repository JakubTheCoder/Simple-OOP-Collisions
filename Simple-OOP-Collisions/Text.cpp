#include "Text.h"

Text::Text(int _x,int _y)
{
	TTF_Init();	//initialize TTF (used for text)

	m_font = TTF_OpenFont("Sans.ttf", 28);	//open font

	m_rect = new SDL_Rect();	//create rect

	m_rect->x = 0;	
	m_rect->y = 0;

	m_texture = NULL;

}

Text::~Text()
{
	if (m_texture != NULL)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
	}
}

bool Text::LoadText(SDL_Renderer* _renderer, std::string _text, SDL_Color _color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(m_font, _text.c_str(), _color);	//creates surface 

	if (surface != NULL)
	{
		//set the size of the text based on the size of thesurface (this way text can be as long as it needs to be without us needing to know what the values are)
		m_rect->w = surface->w;	
		m_rect->h = surface->h;

		if (m_texture != NULL)	//Destroy last texture if object exists
		{
			SDL_DestroyTexture(m_texture);
		}

		m_texture = SDL_CreateTextureFromSurface(_renderer, surface); //create new texture 

		SDL_FreeSurface(surface);	//delete surface
	}
	else
	{
		printf(TTF_GetError());	//if TTF has any problems initializing etc. (It did)
	}

	return m_texture != NULL;
}

void Text::Draw(SDL_Renderer* _renderer, int _x, int _y)
{
	m_rect->x = _x;
	m_rect->y = _y;
	if (m_texture != NULL)
	{
		SDL_RenderCopy(_renderer, m_texture, NULL, m_rect);
	}
}