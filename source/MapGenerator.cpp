#include "MapGenerator.h"
#include "Wall.h"

#include <random>
#include <iostream>

/**
 * Creates map generator with params
 * @param x - X size of map
 * @param y - Y size of map
 * @param seedStr - text that defines map
*/
MapGenerator::MapGenerator(const uint32_t& x, const uint32_t& y, const std::string& seedStr, uint8_t steps)
	: fields(x*y), seed(std::atoi(seedStr.c_str())), sizeX(x), sizeY(y), elementSize(50)
{
	initialize();

	for (uint8_t i = 0; i < steps; ++i)
		doSimulation();

	for (uint32_t j = 0; j < y; ++j)
	{
		for (uint32_t i = 0; i < x; ++i)
		{
			if (fields[j*x + i] == MapField::Empty)
				std::cout << " ";
			else
				std::cout << "X";
		}
		std::cout << std::endl;
	}
}

/**
* Return X size of map
*/
inline uint32_t MapGenerator::getX() const
{
	return sizeX;
}

/*
* Return Y size of map
*/
inline uint32_t MapGenerator::getY() const
{
	return sizeY;
}

/*
* Initializes random generator and generates basic map
*/
void MapGenerator::initialize()
{
	//	srand(seed);
	int toss = 0;
	for (auto& field : fields)
	{
		toss = rand() % 7;
		if (toss == 1)
			field = MapField::Wall;
		else
			field = MapField::Empty;
	}
}

/**
* Makes smoother map
*/
void MapGenerator::doSimulation()
{
	std::vector<MapField> newMap(sizeX*sizeY);
	uint32_t mapSize = sizeX;

	auto nbh = [&newMap, mapSize](uint32_t x, uint32_t y) -> MapField&
	{
		return newMap[y*mapSize + x];
	};

	int aliveNbh;
	for (uint32_t j = 0; j < sizeY; ++j)
	{
		for (uint32_t i = 0; i < sizeX; ++i)
		{
			aliveNbh = countAlive(i, j);
			if (getField(i, j) == MapField::Wall)
			{
				if (aliveNbh < 3)
					nbh(i, j) = MapField::Empty;
				else
					nbh(i, j) = MapField::Wall;
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

/**
* Counts Entities around field
*/
int MapGenerator::countAlive(uint32_t x, uint32_t y) const
{
	int alive = 0;
	int nbhX;
	int nbhY;
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			nbhX = x + i;
			nbhY = y + j;
			if (i == j && i == 0)
				continue;
			else if (nbhX < 0 || nbhX >= static_cast<int>(sizeX) || nbhY < 0 || nbhY >= static_cast<int>(sizeY))
				++alive;
			else if (getField(static_cast<uint32_t>(nbhX), static_cast<uint32_t>(nbhY)) != MapField::Empty)
				++alive;
		}
	}

	return alive;
}

sf::Vector2f MapGenerator::getStartPoint() const
{
	bool found = false;
	uint32_t x, y;
	while (!found)
	{
		x = rand() % sizeX;
		y = rand() % sizeY;

		if (countAlive(x, y) == 0)
			found = true;
	}

	return sf::Vector2f(static_cast<float>(x*elementSize), static_cast<float>(y*elementSize));
}

/**
* Gets field.
* @param x - x axis coordinate
* @param y - y axis coordinate
* @return field at [x,y] position
*/
MapField& MapGenerator::getField(const uint32_t& x, const uint32_t& y)
{
	return fields[y*sizeX + x];
}

/**
* Gets field.
* @param x - x axis coordinate
* @param y - y axis coordinate
* @return field at [x,y] position
*/
MapField MapGenerator::getField(const uint32_t& x, const uint32_t& y) const
{
	return fields[y*sizeX + x];
}

void MapGenerator::setField(const uint32_t& x, const uint32_t& y, const MapField& field)
{
	fields[static_cast<uint32_t>(y / elementSize)*sizeX + static_cast<uint32_t>(x / elementSize)] = field;
}

/**
* Checks if field is empty
* @param x - x axis
* @param y - y axis
* @return bool if is empty
*/
bool MapGenerator::isEmpty(const float& x, const float& y) const
{
	return (getField(static_cast<uint32_t>(x / elementSize), static_cast<uint32_t>(y / elementSize)) == MapField::Empty);
}
