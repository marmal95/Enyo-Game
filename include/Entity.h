
#ifndef ENYO_ENTITY_H
#define ENYO_ENTITY_H

#include "Animation.h"
#include "SceneNode.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>
#include <memory>

class Game;

class Entity : public SceneNode
{
protected:
	sf::Vector2f mVelocity;
    float radius;
    float angle;
    bool life;
    std::string name;
    Animation anim;

    const Game* window;

public:
    Entity();
    Entity(const Game* window, const std::string& name, const Animation& animation,
          const sf::Vector2f& position, const float& angle = 0, const float& radius = 1);
    ~Entity();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update() override;

    float getRadius() const;
    float getAngle() const;
    bool getLife() const;
    Animation& getAnimation();
    const std::string& getName() const;
    void setAnimation(const Animation& animation);
    void addAngle(float value);
    void subAngle(float value);
    void setLife(bool life);

	//void setPosition(const sf::Vector2f& position);
	//void setPosition(float x, float y);
	//sf::Vector2f getPosition() const;

	void setVelocity(const sf::Vector2f& velocity);
	void setVolocity(float dx, float dy);
	sf::Vector2f getVolocity() const;


};

#endif //ENYO_ENTITY_H
