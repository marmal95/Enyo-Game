#ifndef ENYO_MAPGENERATOR_H
#define ENYO_MAPGENERATOR_H

#include <vector>
#include <string>

enum class MapField{
	Empty,
	Wall
};


class MapGenerator
{
	std::vector<MapField> fields;
	int seed;
	uint32_t sizeX;
	uint32_t sizeY;
public:
	MapGenerator(const uint32_t& x, const uint32_t& y, const std::string& seedStr, uint8_t steps = 5);
	~MapGenerator();

	uint32_t getX() const;
	uint32_t getY() const;

private:
	void initialize();
	void doSimulation();
	int countAlive(uint32_t x, uint32_t y);
	MapField& getField(uint32_t x, uint32_t y);
};

#endif // !ENYO_MAPGENERATOR_H
