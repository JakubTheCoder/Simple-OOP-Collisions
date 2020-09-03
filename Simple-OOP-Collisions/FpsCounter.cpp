#include "FpsCounter.h"

FpsCounter::FpsCounter(int _x, int _y)
	:Text(_x, _y)
{
	m_startTicks = 0;
	m_rect->x = 0;
	m_rect->y = 0;

	m_currentFPS = 0;
}
FpsCounter::~FpsCounter()
{

}

void FpsCounter::Start()
{
	m_startTicks = SDL_GetTicks();	//start counting the ticks
}

void FpsCounter::CalcFPS()
{
	m_deltaTicks = SDL_GetTicks() - m_startTicks;	//calculates how mamny ticks have passed based on time
	m_startTicks = SDL_GetTicks();

	if (m_deltaTicks != 0)
	{
		m_currentFPS = 1000 / m_deltaTicks;
	}
}

Uint32 FpsCounter::GetTicks()
{
	Uint32 time = 0;
	time = SDL_GetTicks() - m_startTicks;
	return time;
}
