
#include "Entity.h"

#include <SFML/Graphics/CircleShape.hpp>

/**
 * Initializes Entity Object.
 */
Entity::Entity()
        : x_pos(0), y_pos(0), dx(0), dy(0), radius(0), angle(0), life(true), name(""), anim()
{}

/**
 * Initializes Entity Object.
 * @param name object name
 * @param animation object animation
 * @param x x - axis position
 * @param y y - axis position
 * @param angle direction angle
 * @param radius object radius
 */
Entity::Entity(const Game* window, const std::string &name, const Animation &animation, const int &x, const int &y, const float &angle,
               const float &radius)
        : x_pos(static_cast<float>(x)), y_pos(static_cast<float>(y)), dx(0.F), dy(0.F), radius(radius), angle(angle), life(true), name(name), anim(animation), window(window)
{}

/**
 * Destructs Entity Object.
 */
Entity::~Entity()
{}

/**
 * Set Entity Object Data.
 * @param animation object animation
 * @param x x - axis position
 * @param y y - axis position
 * @param angle direction angle
 * @param radius object radius
 */
void Entity::setData(const Animation &animation, const int &x, const int &y, const float &angle, const float &radius)
{
    this->x_pos = static_cast<float>(x);
    this->y_pos = static_cast<float>(y);
    this->angle = angle;
    this->radius = radius;
    this->anim = anim;
}

/**
 * Draws Object on Screen.
 * @param window game window
 */
void Entity::draw(sf::RenderWindow &window)
{
    this->anim.setSpritePos(this->x_pos,this->y_pos);
    this->anim.setSpriteRot(this->angle+90);
    window.draw(this->anim.getSprite());

//     DEBUG
//     Displays Circle Around Object

    sf::CircleShape circle(this->radius);
    circle.setFillColor(sf::Color(255,0,0,170));
    circle.setPosition(this->x_pos,this->y_pos);
    circle.setOrigin(this->radius,this->radius);
    window.draw(circle);
}

float Entity::getXPos() const
{
    return x_pos;
}

float Entity::getYPos() const
{
    return y_pos;
}

float Entity::getDx() const
{
    return dx;
}

float Entity::getDy() const
{
    return dy;
}

float Entity::getRadius() const
{
    return radius;
}

float Entity::getAngle() const
{
    return angle;
}

bool Entity::getLife() const
{
    return life;
}

Animation& Entity::getAnimation()
{
    return anim;
}

const std::string& Entity::getName() const
{
    return name;
}

void Entity::setAnimation(const Animation& animation)
{
    anim = animation;
}

void Entity::addAngle(float value)
{
    angle += value;
}

void Entity::subAngle(float value)
{
    angle -= value;
}

void Entity::setLife(bool life)
{
    this->life = life;
}

void Entity::setDx(float dx)
{
    this->dx = dx;
}

void Entity::setDy(float dy)
{
    this->dy = dy;
}