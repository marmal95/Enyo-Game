#ifndef ENYO_MAPGENERATOR_H
#define ENYO_MAPGENERATOR_H

#include <vector>
#include <string>
#include "Entity.h"

enum class MapField{
	Empty,
	Wall
};

class MapGenerator
{
private:
	uint32_t elementSize;
	std::vector<MapField> fields;
	int seed;
	uint32_t sizeX;
	uint32_t sizeY;

	void initialize();
	void doSimulation();
	int countAlive(uint32_t x, uint32_t y) const;

public:
	MapGenerator(const uint32_t& x, const uint32_t& y, const std::string& seedStr, uint8_t steps = 5);

	uint32_t getX() const;
	uint32_t getY() const;
	MapField& getField(uint32_t x, uint32_t y);
	MapField getField(uint32_t x, uint32_t y) const;
	bool isEmpty(const float& x, const float& y) const;
	sf::Vector2f getStartPoint() const;
};

#endif // !ENYO_MAPGENERATOR_H
