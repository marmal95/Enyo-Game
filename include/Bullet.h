
#ifndef ENYO_BULLET_H
#define ENYO_BULLET_H

#include "Entity.h"

class Bullet : public Entity
{
public:
    Bullet(const GamePlay* window, const Animation& animation, const Vector<float>& position,
		const float& angle, const float& radius);
    void update(float dt) override;
};

#endif //ENYO_BULLET_H
