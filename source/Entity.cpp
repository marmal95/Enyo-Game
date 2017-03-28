
#include "Entity.h"

#include <SFML/Graphics/CircleShape.hpp>

/**
 * Initializes Entity Object.
 * @param name object name
 * @param animation object animation
 * @param x x - axis position
 * @param y y - axis position
 * @param angle direction angle
 * @param radius object radius
 */
Entity::Entity(const World* window, const std::string &name, const Animation &animation, const sf::Vector2f& position, const float &angle,
               const float &radius)
        : mVelocity(0, 0), radius(radius), life(true), name(name), anim(animation), window(window)
{
	setPosition(position);
	setRotation(angle);
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
	this->anim.setSpriteRot(getRotation() + 90);
}

float Entity::getRadius() const
{
    return radius;
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

void Entity::setLife(bool life)
{
    this->life = life;
}

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
