#pragma once

#include "Vector.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <cstdint>


class Animation
{
private:
	float frame;
	float speed;
	sf::Sprite sprite;
	std::vector<sf::IntRect> frames;

public:
	Animation();
	Animation(const sf::Texture& t, const uint32_t& w, const uint32_t& h, const uint32_t& count, const float& speed);

	void setSpritePos(const float& x_pos, const float& y_pos);
	void setSpriteRot(const float& rot);

	const sf::Sprite& getSprite() const;

	void update();
	bool finished();
};
