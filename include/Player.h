#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
    bool moving;

public:
    Player(const World* window, const Animation &animation, const sf::Vector2f& position, const float &angle = 0, const float &radius = 1);
    void update() override;
    bool isMoving() const;
    void setMoving(bool moving);
};
