
#ifndef ENYO_ASTEROID_H
#define ENYO_ASTEROID_H

#include "Entity.h"

class Asteroid : public Entity
{
public:
    Asteroid(const GamePlay* window, const Animation& animation, const Vector<float>& position,
		const float& angle, const float& radius);
    void update(float dt) override;
};

#endif //ENYO_ASTEROID_H
