#pragma once

#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>

enum class MapField
{
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

	MapField getField(const uint32_t& x, const uint32_t& y) const;
	bool isEmpty(const float& x, const float& y) const;
	bool canSpawn(const float& x, const float& y, const float& radius);
	sf::Vector2f getStartPoint() const;
};