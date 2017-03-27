
#ifndef ENYO_PLAYER_H
#define ENYO_PLAYER_H

#include "Entity.h"

class Player : public Entity
{
private:
    bool moving;

public:
    Player(const Game* window, const Animation &animation, const int &x, const int &y, const float &angle = 0, const float &radius = 1);
    void update() override;
    bool isMoving() const;
    void setMoving(bool moving);
};

#endif //ENYO_PLAYER_H
