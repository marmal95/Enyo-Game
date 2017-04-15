#ifndef ENYO_MAPGENERATOR_H
#define ENYO_MAPGENERATOR_H

#include <vector>
#include <string>
#include "Entity.h"

enum class MapField
{
	Empty,
	Wall,
	Asteroid
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
	MapField& getField(const uint32_t& x, const uint32_t& y);
	MapField getField(const uint32_t& x, const uint32_t& y) const;
	void setField(const uint32_t& x, const uint32_t& y, const MapField& field);
	bool isEmpty(const float& x, const float& y) const;
	sf::Vector2f getStartPoint() const;
};

#endif // !ENYO_MAPGENERATOR_H
