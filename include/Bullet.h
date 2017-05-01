#pragma once

#include "Entity.h"

class Bullet : public Entity
{
public:
    Bullet(const Animation& animation, const Vector<float>& position,
		const float& angle, const float& radius);
    void update(float dt) override;
};
