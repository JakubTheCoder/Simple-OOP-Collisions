#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <time.h>
#include <vector>
#include <sstream>
#include <string>

#include "Particle.h"
#include "Bucket.h"
#include "HashTable.h"
#include"FpsCounter.h"
#include "Text.h"

// SDL initialisation functions
bool InitialiseSDL();
SDL_Window* CreateSDLWindow(char* title, int xPos, int yPos, int width, int height);
SDL_Renderer* CreateSDLRenderer(SDL_Window* window);

//Screem Sizes
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)

//Game Functions
void GameLoop(SDL_Renderer* renderer);
bool CheckExit();

int main(int, char**)
{
	//SDL Setting Up Window and making sure everything is initialised and working

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	srand(time(NULL));

	bool initialiseOK = InitialiseSDL();

	if (initialiseOK)
	{
		window = CreateSDLWindow("Particle Collision", 100, 100, SCREEN_WIDTH+10, SCREEN_HEIGHT+10);
	}

	if (window != NULL)
	{
		renderer = CreateSDLRenderer(window);
	}

	if (!initialiseOK || !window || !renderer)
	{
		std::cout << "Initialisation of SDL failed\n";
		system("pause");
		return 0;
	}

	//MAIN LOOP
	GameLoop(renderer);

	//Clean up SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}


bool InitialiseSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
		return false;
	}

	return true;
}

SDL_Window* CreateSDLWindow(char* _title, int _xPos, int _yPos, int _width, int _height)
{
	//CREATES WINDOW
	SDL_Window* window = SDL_CreateWindow(_title, _xPos, _yPos, _width, _height, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return NULL;
	}

	return window;
}

SDL_Renderer* CreateSDLRenderer(SDL_Window* window)
{
	//CREATES RENDERER
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return NULL;
	}

	return renderer;
}

bool CheckExit()
{
	// detect if the window is being closed

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			return false;
	}

	return true;
}

void GameLoop(SDL_Renderer* _renderer)
{
	bool running = true; // for the while loop below to use

	FpsCounter fpsCounter(0,0);	//creates fps counter

	Text particleText(0, 0);	//Text for number of particles

	const Uint8* keys = SDL_GetKeyboardState(NULL);	//Keyboard inputs

	SDL_Color textColor = { 0,255,0 };	//Set color of text

	std::stringstream fpsText;	//String for FPS Text
	std::stringstream particlesText;	//String for Particle count text

	int sizeOfParticles = 2000;// Number of particles to start with

	int bucketSize = 50;	//Size of each bucket

	int gridWidth = 16;		//16 buckets going across (screen width (800) / bucket size(50)
	
	int gridHeight = 12;	//12 buckets going down (screen height (600) / bucket size(50)

	std::vector<Bucket*> buckets;	//vector of buckets (Physical GRID) 

	HashTable hashTable(gridWidth*gridHeight);	//hash table 

	for (int y = 0; y < gridHeight; ++y)	//Drawing the grid
	{
		for (int x = 0; x < gridWidth; ++x)
		{
			Bucket* bucket = new Bucket(_renderer, "Particle.bmp", 5, 5, bucketSize);
			bucket->SetPosition(x * bucketSize, y * bucketSize);
			buckets.push_back(bucket);
		
		}
	}

	std::vector<Particle*> particles;	//Vector of particles 
	for (int i = 0; i < sizeOfParticles; ++i)	//Creates particles (based on how many there are (2000))
	{
		Particle* particle = new Particle(_renderer, "Particle.bmp", 2, 2,&hashTable);
		particles.push_back(particle);
		hashTable.AddParticle(particle->GetPosX(), particle->GetPosY(), particle, bucketSize, gridWidth);	//and adds them into the hash table
	}
	/*for (int i = 0; i < hashTable.GetSize(); ++i)
	{
		std::cout << i << ": " << hashTable.GetPartitionSize(i) << std::endl;
	}
*/
	
	while (running) // each iteration of this loop is one frame
	{
		running = CheckExit();	//checks if the program has been closed
		fpsCounter.Start();	//Start the fps counter

		//KEY PRESSES 

		if (keys[SDL_SCANCODE_SPACE])	//SPACE infects a random particle
		{
			particles.at(rand() % particles.size())->SetInfected(true);
		}  

		if (keys[SDL_SCANCODE_1])	//1 increases the number of particles
		{
			for (int i = 0; i < 45; ++i)
			{
				Particle* particle = new Particle(_renderer, "Particle.bmp", 2, 2, &hashTable);
				particles.push_back(particle);
				hashTable.AddParticle(particle->GetPosX(), particle->GetPosY(), particle, bucketSize, gridWidth);

			}
			//Clears the table and re adds all the particles into hash table
			//This was made because there were random amounts (in billions) of objects being made for no reason
			hashTable.Clear();
			for (int i = 0; i < particles.size(); ++i)
			{
				hashTable.AddParticle(particles.at(i)->GetPosX(), particles.at(i)->GetPosY(), particles.at(i), bucketSize, gridWidth);
			}
		}
		if (keys[SDL_SCANCODE_2])	//2 Decreases the number of particles
		{
			if (particles.size() <= 110)	//If particles is less than or equal to 100 DO NOTHING, we dont want to remove more particles (value may go down if number is e.g. 110, particles will minus once)
			{

			}
			else
			{
				for (int i = 0; i < 10; ++i)	
				{
					particles.erase(particles.begin(), particles.begin() + i);// remove the particles from the particle vector
					//Was unable to get the deleted particles to remove from hash, so the whole hash had to be cleared
					hashTable.Clear();	//clears hash table
				}
				for (int i = 0; i < particles.size();++i)	//re add all the particles to the hash table
				{
					hashTable.AddParticle(particles.at(i)->GetPosX(), particles.at(i)->GetPosY(), particles.at(i), bucketSize, gridWidth);
				}
			}

		}
		if (keys[SDL_SCANCODE_3])	//3 Resets the infected
		{
			for (int i = 0; i < particles.size(); ++i)
			{
				particles.at(i)->SetInfected(false);
			}
		}
		//Update on Particles
		for (int i = 0; i < particles.size(); ++i)
		{
			particles.at(i)->Update();
		}

		SDL_RenderClear(_renderer); // wipe the "frame" clean

		//DRAWS
		for (int i = 0; i < particles.size(); ++i)	//Draws particles
		{
			particles.at(i)->Draw(_renderer,particles.at(i)->GetPosX(),particles.at(i)->GetPosY());
		}
		for (int i = 0; i < buckets.size(); ++i)	//Draws Buckets
		{
			buckets.at(i)->Draw(_renderer, buckets.at(i)->GetPosX(), buckets.at(i)->GetPosY());
		}

		fpsCounter.CalcFPS();	//calculate the fps
		fpsText.str("");
		fpsText << "FPS: " << fpsCounter.GetCurrentFPS();	//set text to FPS 

		fpsCounter.LoadText(_renderer, fpsText.str(), textColor);	//load text

		particlesText.str("");
		particlesText << "Num of Particles: " << particles.size();	//set text to number or particles 

		particleText.LoadText(_renderer, particlesText.str(), textColor);	//load text

		fpsCounter.Draw(_renderer, 0, 0);	//Draw fps text
		particleText.Draw(_renderer, 0, 30);	//Draw particle count text

		SDL_RenderPresent(_renderer); // send the frame to the screen

	}

	//Deletes all items
	for (int i = 0; i < particles.size(); ++i)
	{
		delete particles.at(i);
	}
	for (int i = 0; i < buckets.size(); ++i)
	{
		delete buckets.at(i);
	}
}