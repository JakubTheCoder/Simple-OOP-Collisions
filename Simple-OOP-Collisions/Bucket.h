#pragma once
#ifndef _BUCKET_H_
#define _BUCKET_H_

#include <SDL.h>
#include <vector>

#include "Sprite.h"

class Bucket : public Sprite
{
public:
	Bucket(SDL_Renderer* _renderer, char* _filename, int _w, int _h,int _size);	//constructor
	~Bucket();	//destructor
	void SetPosition(int _x, int _y);	//set position of the bucket
	int GetPosX() { return m_posRect.x; }//Get X
	int GetPosY() { return m_posRect.y; }//Get Y
	void Draw(SDL_Renderer* _renderer, int _x, int _y); //Draw

	std::vector<Bucket*>m_bucketList;	//Vector of all the buckets (grid)

private:
	int m_bucketSize;	//size of buckets 

};
#endif 
