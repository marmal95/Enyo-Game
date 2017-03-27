#include "MapGenerator.h"

#include <random>
#include <iostream>

/**
 * Creates map generator with params
 * @param x - X size of map
 * @param y - Y size of map
 * @param seedStr - text that defines map
*/
MapGenerator::MapGenerator(const uint32_t & x, const uint32_t & y, const std::string & seedStr, uint8_t steps)
	: fields(x*y), seed(std::atoi(seedStr.c_str())), sizeX(x), sizeY(y)
{	
	initialize();

	for(uint8_t i = 0; i < steps; ++i)
		doSimulation();


	for (int j = 0;j < y; ++j)
	{
		for (int i = 0; i < x; ++i)
		{
			std::cout << static_cast<uint8_t>(fields[j*x+i]);
		}
		std::cout << std::endl;
	}
}

MapGenerator::~MapGenerator()
{
}

/*
* Return X size of map
*/
inline uint32_t MapGenerator::getX() const
{
	return sizeX;
}

/*
* Return Y size of map
*/
inline uint32_t MapGenerator::getY()
{
	return sizeY;
}

/*
* Initializes random generator and generates basic map
*/
void MapGenerator::initialize()
{
	srand(seed);
	int toss = 0;
	for (auto& field : fields)
	{
		toss = rand()%7;
		if(toss == 1)
			field = MapField::Wall;
		else
			field = MapField::Empty;
	}
}

void MapGenerator::doSimulation()
{
	std::vector<MapField> newMap(sizeX*sizeY);
	uint32_t mapSize = sizeX;
	auto nbh = [&newMap, mapSize](uint32_t x, uint32_t y)->MapField& {
		return newMap[y*mapSize +x];
	};


	int aliveNbh;
	for (uint32_t j = 0;j < sizeY; ++j)
	{
		for (uint32_t i = 0; i < sizeX; ++i)
		{
			aliveNbh = countAlive(i,j);
			if (getField(i, j) == MapField::Wall)
			{
				if(aliveNbh < 3)
					nbh(i,j) = MapField::Empty;
				else
					nbh(i,j) = MapField::Wall;
			}
			else
			{
				if (aliveNbh >= 3)
					nbh(i, j) = MapField::Wall;
				else
					nbh(i, j) = MapField::Empty;
			}
		}
	}
	fields = newMap;
}

int MapGenerator::countAlive(uint32_t x, uint32_t y)
{
	int alive = 0;
	int nbhX = x;
	int nbhY = y;
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			nbhX = x + i;
			nbhY = y + j;
			if (i == j && i == 0)
				continue;
			else if (nbhX < 0 || nbhX >= sizeX || nbhY < 0 || nbhY >= sizeY)
				++alive;
			else
				if(getField(nbhX, nbhY) != MapField::Empty)
					++alive;
		}
	}

	return alive;
}

MapField& MapGenerator::getField(uint32_t x, uint32_t y)
{
	return fields[y*sizeX + x];
}
