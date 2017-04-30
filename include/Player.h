#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
    bool moving;

public:
    Player(const GamePlay* window, const Animation& animation, const Vector<float>& position,
		const float& angle, const float& radius);

    void update(float dt) override;
    bool isMoving() const;
    void setMoving(bool moving);
};
