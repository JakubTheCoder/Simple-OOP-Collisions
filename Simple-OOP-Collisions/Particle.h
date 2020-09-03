#pragma once
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <SDL.h>

#include "Sprite.h"
class HashTable;

struct Vector2	//used for speed
{
	float m_x;
	float m_y;
};

class Particle :public Sprite
{
public :
	Particle(SDL_Renderer* _renderer, char* _filename, int _w, int _h, HashTable* _hashTable); //constructor
	~Particle();	//destructor
	
	int GetPosX() { return m_posRect.x; }	//Get X 
	int GetPosY() { return m_posRect.y; }	//Get Y

	void SetPos(int _x, int _y) { m_posRect.x = _x; m_posRect.y = _y; }	//Set Position

	void Update();	//Update particle 

	void Draw(SDL_Renderer* _renderer,int _x, int _y);	//Draw

	bool IsInfected() { return m_infected; }	//Checks if particle is infected (green)
	void SetInfected(bool _infected) { this->m_infected = _infected; }	//Sets particle's infection type (infeced or not)

	void SetSpeedX(){ m_velocity.m_x *= -1; }	//Makes Particle go in opposite direction in x
	void SetSpeedY(){ m_velocity.m_y *= -1; }	//Makes Particle go in opposite direction in y
	
private:
	Vector2 m_velocity;	//speed & direction of particle
	SDL_Texture*m_infectedSprite;	//Green texture for particle 
	SDL_Rect m_posRect;	//position of particle
	HashTable* m_hashTable;	//reference to hash table
	int m_currentHash;	//currect hash of particle
	bool m_infected;	//infected bool 
};
#endif