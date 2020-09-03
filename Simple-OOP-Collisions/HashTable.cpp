#include "HashTable.h"

#define CELL_SIZE (50)
#define GRID_WIDTH (16)
HashTable::HashTable(unsigned int _size)
{
	m_table.clear(); //clears table at initialization

	for (int i = 0; i < m_tableSize; ++i)	//fills hash table with temp data
	{
		std::vector<Particle*>temp;
		m_table.push_back(temp);

	}
}

HashTable::~HashTable()
{
	Clear();
}
void HashTable::Clear()	//clears the hash table
{
	for (int i = 0; i < m_tableSize; ++i)
	{
		m_table[i].clear();
	}
	m_table.clear();
}
unsigned int HashTable::GenerateHash(int _x,int _y)	//Generates hash index
{
	unsigned value = (((_y / CELL_SIZE) * GRID_WIDTH) + (_x / CELL_SIZE));// hash the index based on the position of the particle

	//Another row of grid has to be drawn to fill the physical screen
	if (value >= m_tableSize)	//this if makes sure we dont add those extra buckets that are off screen into the calculations, making sure we have the right number of buckets
	{
		value = m_tableSize - 1;
	}

	return value;
}
Particle* HashTable::GetParticle(int _x,int _y, int _cellSize, int _cellWidth)
{
	int hashIndex = GenerateHash(_x,_y);	//generate hash index 

	for (int i = 0; i < m_table[hashIndex].size(); ++i)	//finds and returns a particle by comparing the x and y
	{
		if ((m_table[hashIndex].at(i)->GetPosX()== _x)&& (m_table[hashIndex].at(i)->GetPosY() == _y)) 
		{
			return m_table[hashIndex].at(i);
		}
	}
	return nullptr;
}
void HashTable::AddParticle(int _x,int _y, Particle* _particle,int _cellSize,int _cellWidth)	//Adds particle to the hash table
{
	int hashIndex = GenerateHash(_x, _y);
	_particle->SetPos(_x, _y);

	m_table[hashIndex].push_back(_particle);

}