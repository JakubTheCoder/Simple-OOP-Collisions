#include "Particle.h"
#include "HashTable.h"
#include "Collision.h"

#include <time.h>
#include <stdlib.h>

Particle::Particle(SDL_Renderer* _renderer, char* _filename, int _w, int _h, HashTable* _hashTable)
	:Sprite(_renderer, _filename, _w, _h)
{
	SDL_Surface* imageFile = SDL_LoadBMP(_filename);	//Creates Surface
	m_infectedSprite = SDL_CreateTextureFromSurface(_renderer, imageFile);	//Loads Texture 
	SDL_SetTextureColorMod(m_infectedSprite, 0, 255, 0);	//changes color of infected sprite to green
	if (imageFile != NULL)	//if image file is not null == if image file exists
	{
		SDL_FreeSurface(imageFile);	//free up the surface
	}
	m_posRect.w = _w;
	m_posRect.h = _h;
	m_posRect.x = rand() % 800;	//random position on screen in X (width)
	m_posRect.y = rand()%600;	//random position on screen in Y (height)
	m_velocity.m_x = rand() % 6 -3;	//random speed & direction in X(range is -3 to 3)
	m_velocity.m_y = rand() % 6 -3;	//random speed & direction in Y (range is -3 to 3)
	this->m_hashTable = _hashTable;	
	m_currentHash = 0;
	m_infected = false;	//all particles start as non infected
}

Particle::~Particle()
{
	//if successfully created a object, delete it
	if (m_infectedSprite != NULL)
	{
		SDL_DestroyTexture(m_infectedSprite);
	}
}

void Particle::Update()
{
	if ((m_velocity.m_x == 0) && (m_velocity.m_y == 0))	//makes sure particle's speed is not 0,0 -> makes sure particle moves in at least one direction
	{
		m_velocity.m_x = rand() % 6 - 3;	//if not randomise values again
		m_velocity.m_y = rand() % 6 - 3;
	}
	if (m_posRect.x > 800 || m_posRect.x < 0)	//bounce of screen boundries
	{
		SetSpeedX();
	}
	if (m_posRect.y > 600 || m_posRect.y < 0)	//bounce of screen boundries
	{
		SetSpeedY();
	}

	int newHash = m_hashTable->GenerateHash(m_posRect.x, m_posRect.y);	//creates a new hash index

	if (newHash != m_currentHash)	//checks if new hash index is not the same as the old one
	{
		// move from -> to
		std::vector<Particle*>&from = m_hashTable->GetPartition(m_currentHash);	//vector of particles that are moving FROM current bucket into a new bucket
		std::vector<Particle*>&to = m_hashTable->GetPartition(newHash);	//vector if oartuckes that are moving TO a new bucket

		to.push_back(this);
		for (int i = 0; i < from.size(); ++i)	//deletes the from bucket, as the particles have left
		{
			if (from.at(i) == this)
			{
				from.erase(from.begin() + i);
				break;
			}
		}
		m_currentHash = newHash;	//sets new hash index as current hash index after the particle has moved 
	}

	std::vector<Particle*>&bucket = m_hashTable->GetPartition(m_currentHash);	//checks particles inside partiotion (bucket)

	for (int i = 0; i < bucket.size(); ++i)	// go through bucket vector
	{
		if (bucket.at(i) == this)	//if a particle is itself move on (cant collide with itself )
		{
			continue;
		}

		if (Collision::colliding(GetPosX(), GetPosY(), bucket.at(i)->GetPosX(), bucket.at(i)->GetPosY()))	//check collision between 2 particles inside this bucket vector
		{
			if (m_infected)	//if a particle is infected, make the particle it collided with also infected
			{
				bucket.at(i)->SetInfected(true);

			}
			//Make the particles bounce
			//Only bounces the other particle as bouncing both could cause them to shake back and forth.
			//setSpeedX();
			//setSpeedY();
			bucket.at(i)->SetSpeedX();
			bucket.at(i)->SetSpeedY();
		}
	}
	//Update the position of the particle
	m_posRect.x += m_velocity.m_x;	
	m_posRect.y += m_velocity.m_y;
}

void Particle::Draw(SDL_Renderer* _renderer,int _x,int _y)
{
	m_posRect.x = _x;
	m_posRect.y = _y;
	//if there is a texture, draw it
	if (m_tex != NULL)
	{
		if (m_infected)	//if particle is infected draw infected texture
		{
			SDL_RenderCopy(_renderer, m_infectedSprite, NULL, &m_posRect);
		}
		else//else draw normal texture
		{
			SDL_RenderCopy(_renderer, m_tex, NULL, &m_posRect);
		}
	}


}