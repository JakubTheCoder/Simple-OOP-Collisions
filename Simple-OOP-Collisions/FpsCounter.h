#pragma once
#ifndef _FPSCOUNTER_H_
#define _FPSCOUNTER_H_

#include "Text.h"
class FpsCounter : public Text
{
public:
	FpsCounter(int _x, int _y);	//constructor	
	~FpsCounter();	//destructor
	Uint32 GetTicks();	//get the number of ticks that have passed
	void Start();	//start the time
	void CalcFPS();	//calculate the frames per second

	int GetCurrentFPS() { return m_currentFPS; }	//getter of calculated fps

private:
	Uint32 m_startTicks;
	Uint32 m_deltaTicks;
	Uint32 m_currentFPS;

};
#endif