#pragma once

#include "Entity.h"

class Wall : public Entity
{
public:
	Wall(const Animation& animation, const Vector<float>& position,
		const float& angle, const float& radius);
	void update(float dt) override;
};