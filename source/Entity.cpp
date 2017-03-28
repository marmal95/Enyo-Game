
#include "Entity.h"

#include <SFML/Graphics/CircleShape.hpp>

/**
 * Initializes Entity Object.
 */
Entity::Entity()
        : mVelocity(0, 0), radius(0), angle(0), life(true), name(""), anim()
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
Entity::Entity(const Game* window, const std::string &name, const Animation &animation, const sf::Vector2f& position, const float &angle,
               const float &radius)
        : mVelocity(0, 0), radius(radius), angle(angle), life(true), name(name), anim(animation), window(window)
{
	setPosition(position);
}

/**
 * Destructs Entity Object.
 */
Entity::~Entity()
{}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(anim.getSprite());
}

void Entity::update()
{
	this->anim.setSpritePos(getPosition().x, getPosition().y);
	this->anim.setSpriteRot(this->angle + 90);
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

//void Entity::setPosition(const sf::Vector2f & position)
//{
//	mPosition = position;
//}
//
//void Entity::setPosition(float x, float y)
//{
//	mPosition.x = x;
//	mPosition.y = y;
//}
//
//sf::Vector2f Entity::getPosition() const
//{
//	return mPosition;
//}

void Entity::setVelocity(const sf::Vector2f & velocity)
{
	mVelocity = velocity;
}

void Entity::setVolocity(float dx, float dy)
{
	mVelocity.x = dx;
	mVelocity.y = dy;
}

sf::Vector2f Entity::getVolocity() const
{
	return mVelocity;
}
