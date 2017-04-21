#pragma once
#include "GameStage.h"

#include "ResourceHolder.hpp"
#include "MapGenerator.h"
#include "Id.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Player.h"



#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <list>
#include <random>

/**
 * GamePlay class controls whole play in game.
 * Must implement pure virtual functions from base class.
 */
class GamePlay : public GameStage
{
private:
	// Game Dimension
	sf::Vector2i worldDimension;

	// Camera
	sf::View mWorldView;

	//Map generator
	MapGenerator generator;

	// Texture Holder
	ResourceHolder<sf::Texture, ID> mTextureHolder;

	// Animation Holder
	ResourceHolder<Animation, ID> mAnimationHolder;

	// Sound Holder
	ResourceHolder<sf::SoundBuffer, ID> mSoundHolder;

	// Sounds
	std::list<sf::Sound> qSounds;

	// Entities List
	std::vector<std::unique_ptr<Entity>> entities;

	// Background Sprite
	sf::Sprite sBackground;

	// Pointer to Player Aircraft
	Player* playerAircraft;

	// ---------------------------

	std::mt19937 mt;
	std::uniform_int_distribution<uint32_t> randDist;

private:
	void initializeWold();
	void buildScene();
	void addWalls();

	void createPlayer();
	void createAsteroids(ID asteroidId, const uint32_t& count);

	void checkPlayerMove();
	void checkCollisions();
	void checkUpdateEntities(float dt);
	void checkRandomAsteroid();
	void checkSounds();

	bool isCollide(const Entity* const a, const Entity* const b);
	void makeBounce(Entity* const a, Entity* const b);

	void asteroidVsBullet(Entity* const a, Entity* const b);
	void playerVsAsteroid(Entity* const a, Entity* const b);
	void playerVsWall(Entity* const a, Entity* const b);

	bool canSpawn(const float& x, const float& y, const float& radius);

public:
	GamePlay(sf::RenderWindow& window, const sf::Vector2i& dimension);

	virtual void init() override;
	virtual bool update(float dt) override;
	virtual void draw(sf::RenderWindow& window) override;
	virtual void release() override;
	virtual void handleUserInput(sf::Keyboard::Key key, bool pressed) override;

	sf::Vector2i getDimension() const;
};