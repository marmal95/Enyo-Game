
#ifndef ENYO_ENTITY_H
#define ENYO_ENTITY_H

#include "Animation.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>
#include <memory>

class Game;

/**
 * Entity Abstract Class.
 */
class Entity
{
protected:
    float x_pos;
    float y_pos;
    float dx;
    float dy;
    float radius;
    float angle;
    bool life;
    std::string name;
    Animation anim;

    const Game* window;

public:
    Entity();

    Entity(const Game* window, const std::string& name, const Animation& animation,
           const int& x, const int& y, const float& angle = 0, const float& radius = 1);

    ~Entity();

    virtual void update() = 0;

    void setData(const Animation& animation, const int& x, const int& y,
                 const float& angle = 0, const float& radius = 1);

    void draw(sf::RenderWindow& window);


    float getXPos() const;

    float getYPos() const;

    float getDx() const;

    float detDy() const;

    float getRadius() const;

    float getAngle() const;

    bool getLife() const;

    Animation& getAnimation();

    const std::string& getName() const;

    void setAnimation(const Animation& animation);

    void addAngle(float value);

    void subAngle(float value);

    void setLife(bool life);

    void setDx(float dx);

    void setDy(float dy);
};

#endif //ENYO_ENTITY_H
