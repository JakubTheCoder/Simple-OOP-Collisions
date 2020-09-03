#pragma once
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <SDL.h>
#include <vector>

#include "Particle.h"

class HashTable
{
	
public:

	HashTable(unsigned int _size);	//consturctor
	~HashTable();	//destructor
	unsigned int GenerateHash(int _x, int _y);	//generates the hash index

	Particle* GetParticle(int _x, int _y, int _cellSize, int _cellWidth);	//Gets a particle from hash table
	void AddParticle(int _x, int _y, Particle* _particle, int _cellSize, int _cellWidth);	//Adds a particle into hash table

	int GetSize() { return m_tableSize; }	//Gets the size of the table

	int GetPartitionSize(int _i) { return m_table[_i].size(); }	//Gets size of particles in a partition (bucket)

	void Clear();	//clears the hash table
	std::vector<Particle*>&GetPartition(int index) { return m_table[index]; } // get a partition (bucket)
private:
	  int m_tableSize = 192; // Hash table size

	std::vector<std::vector<Particle*>> m_table;   //vector of buckets that holds vector of particles
};
#endif