#include "Bucket.h"

Bucket::Bucket(SDL_Renderer* _renderer, char* _filename, int _w, int _h, int _bucketSize)
	:Sprite(_renderer,_filename,_w,_h)
{

	SDL_SetTextureColorMod(m_tex, 255, 0, 0);	//Edits the default while pixel sprite to red

	m_posRect.w = _w;	
	m_posRect.h = _h;	

	m_bucketSize = _bucketSize;


}
Bucket::~Bucket()
{

}
void Bucket::SetPosition(int _x, int _y)	//sets position of each 
{
	this->m_posRect.x = _x;
	this->m_posRect.y = _y;
}

void Bucket::Draw(SDL_Renderer* _renderer, int _x, int _y)	//Draw bucket
{
	m_posRect.x = _x;
	m_posRect.y = _y;
	if (m_tex != NULL)	//if texture is not null == if texture exists
	{
		SDL_RenderCopy(_renderer, m_tex, NULL, &m_posRect);	//draw the particle
		SDL_Rect drawRect = m_posRect;	//offset the bucket
		drawRect.y += m_bucketSize;
		drawRect.x += m_bucketSize;
		SDL_RenderCopy(_renderer, m_tex, NULL, &drawRect);
	}
}
