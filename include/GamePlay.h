#pragma once

#include "GameStage.h"
#include "ResourceHolder.hpp"
#include "MapGenerator.h"
#include "Id.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Wall.h"
#include "Player.h"
#include "Explosion.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>

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

	// Font Holder
	sf::Font mFont;
	sf::Text scoreText;

	// Sounds
	std::list<sf::Sound> qSounds;

	// Entities Objects Vectors
	std::vector<Wall> wallVec;
	std::vector<Explosion> exploVec;
	std::vector<Asteroid> asteroidVec;
	std::vector<Bullet> bulletVec;

	// Background Sprite
	sf::Sprite sBackground;

	// Pointer to Player Aircraft
	std::unique_ptr<Player> playerAircraft;

	// Random Generator
	std::mt19937 mt;
	std::uniform_int_distribution<uint32_t> randDist;

	uint32_t scorePoints;

private:
	// Init Game
	void initializeWold();
	void buildScene();

	// Build Game World
	void addWalls();
	void createPlayer();
	void createAsteroids(ID asteroidId, const uint32_t& count);

	// Check Events
	void checkPlayerMove();
	void checkCollisions();
	void checkRandomAsteroid();

	// Update resources
	void updateText();
	void checkSounds();

	// Update Entities
	void updateEntities(float dt);
	void updateWalls(float dt);
	void updateExplosions(float dt);
	void updateAsteroids(float dt);
	void updateBullets(float dt);

	// Check / React collisions
	bool isCollide(const Entity& a, const Entity& b);
	void makeBounce(Entity& a, Entity& b);

	void asteroidVsBullet(Entity& a, Entity& b);
	void playerVsAsteroid(Entity& a, Entity& b);
	void playerVsWall(Entity& a, Entity& b);

	// Check spawn possibility
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