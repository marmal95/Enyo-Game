#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

#include "Animation.h"
#include "Id.h"
#include "Vector.hpp"

#include <string>

#ifndef M_PI
constexpr float M_PI = 3.141592F;
#endif // !M_PI

class GamePlay;

class Entity : public sf::Drawable, public sf::Transformable
{
protected:
	// Entity's Force
	Vector<float> mForce;

	// Entity's Actual Velocity
	Vector<float> mVelocity;

	// Entity's Radius
    float radius;

	// Indicates if entity is alive
    bool life;

	// Entity's Id
	EntityId id;

	// Animated Sprite 
    Animation anim;

	// Game Window
    const GamePlay* window;

public:
    Entity(const GamePlay* window, const Animation& animation,
		const Vector<float>& position, const float& angle, const float& radius);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(float dt);

	void setVelocity(const Vector<float>& velocity);
	void setVelocity(float dx, float dy);
	Vector<float> getVelocity() const;
	Vector<float>& getVelocity();

    float getRadius() const;
	EntityId getId() const;

    Animation& getAnimation();
    void setAnimation(const Animation& animation);

    void setLife(bool life);
	bool getLife() const;
};
