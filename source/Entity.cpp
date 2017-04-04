
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
Entity::Entity(const GamePlay *window, const std::string &name, const Animation &animation,
               const sf::Vector2f &position, const float &angle,
               const float &radius)
        : mVelocity(0, 0), radius(radius), life(true), name(name), anim(animation), window(window) {
    setPosition(position);
    setRotation(angle);
}

/**
 * Destructs Entity Object.
 */
Entity::~Entity() {}

/**
 * {@inherit}
 * Draws the Entity on screen.
 * @param target window we draw to
 * @param states -
 */
void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(anim.getSprite());

#ifdef DEBUG
    sf::CircleShape circle(this->radius);
    circle.setFillColor(sf::Color(255, 0, 0, 170));
    circle.setPosition(getPosition());
    circle.setOrigin(radius, radius);
    target.draw(circle);
#endif
}

/**
 * Updates Entity position
 */
void Entity::update() {
    this->anim.setSpritePos(getPosition().x, getPosition().y);
    this->anim.setSpriteRot(getRotation() + 90);
}

/**
 * Gets Entity Radius
 * @return entity radius
 */
float Entity::getRadius() const {
    return radius;
}

/**
 * Gets Entity life
 * @return true if alive, false - otherwise
 */
bool Entity::getLife() const {
    return life;
}

/**
 * Gets Entity Animation
 * @return entity animation
 */
Animation &Entity::getAnimation() {
    return anim;
}

/**
 * Gets Entity name
 * @return name
 */
const std::string &Entity::getName() const {
    return name;
}

/**
 * Set Entity Animation
 * @param animation entity animation
 */
void Entity::setAnimation(const Animation &animation) {
    anim = animation;
}

/**
 * Set Entity life
 * @param life
 */
void Entity::setLife(bool life) {
    this->life = life;
}

/**
 * Set Entity velocity
 * @param velocity Entiy Vector2f velocity
 */
void Entity::setVelocity(const sf::Vector2f &velocity) {
    mVelocity = velocity;
}

/**
 * Set Entity Velocity
 * @param dx x - axis velocity
 * @param dy y - axis velocity
 */
void Entity::setVelocity(float dx, float dy) {
    mVelocity.x = dx;
    mVelocity.y = dy;
}

/**
 * Get Entity Velocity - const
 * @return entity velocity
 */
sf::Vector2f Entity::getVelocity() const {
    return mVelocity;
}

sf::Vector2f &Entity::getVelocity() {
    return mVelocity;
}
