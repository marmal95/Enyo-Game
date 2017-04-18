#include "MapGenerator.h"
#include "Explosion.h"
#include "GamePlay.h"
#include "Wall.h"

#include <SFML/Window/Event.hpp>

#include <cmath>

/**
 * Initializes GamePlay
 * @param window window we play on
 * @param dimension window dimension
 */
GamePlay::GamePlay(sf::RenderWindow& window, const sf::Vector2i& dimension)
	:
	// World View
	worldDimension(dimension), mWorldView(window.getDefaultView()),
	// Resources
	mTextureHolder(), mAnimationHolder(), mSoundHolder(),
	// Additional Containers
	qSounds(), entities(), sBackground(),
	// Map Generator
	generator(39, 24, "z", 1),
	// Random Generator
	mt(std::random_device()()), randDist()
{}

/**
 * Initializes GamePlay.
 */
void GamePlay::init()
{
	initializeWold();
	buildScene();
}

/**
 * Updates Game logic
 * @param dt frame time
 * @return true - if keep updating, false - otherwise
 */
bool GamePlay::update(float dt)
{
	checkPlayerMove();
	checkCollisions();
	checkUpdateEntities(dt);
	checkRandomAsteroid();
	checkSounds();
	
	return true;
}

/**
 * Draws Game objects on screen.
 * @param window window we draw on
 */
void GamePlay::draw(sf::RenderWindow& window)
{
	// Set Camera View
	mWorldView.setCenter(playerAircraft->getPosition());
	window.setView(mWorldView);

	// Draw Background
	window.draw(sBackground);

	// Draw all entities
	for (const auto& i : entities)
		window.draw(*i);
}

/**
 * Releases allocated resources
 */
void GamePlay::release()
{
	// Nothing to release.
}

/**
 * Handles user input
 * @param key key pressed by user
 * @param pressed true - if pressed, false - if released
 */
void GamePlay::handleUserInput(sf::Keyboard::Key key, bool pressed)
{
	switch (key)
	{
		case sf::Keyboard::Space:
			if (pressed)
			{
				entities.push_back(std::make_unique<Bullet>(this, mAnimationHolder.getResource(ID::BulletBlue),
					sf::Vector2f(playerAircraft->getPosition().x, playerAircraft->getPosition().y), playerAircraft->getRotation(), 10.F));

				qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BulletBlueSound)));
				qSounds.back().play();
			}
			break;

		default:
			break;
	}
}

/**
 * Get game dimension
 * @return game dimension
 */
sf::Vector2i GamePlay::getDimension() const
{
	return worldDimension;
}

/**
 * Initializes Game world. Loads resources.
 */
void GamePlay::initializeWold()
{
	mTextureHolder.load(ID::Explosion, "images/type_C.png");
	mTextureHolder.load(ID::RockBig, "images/rock.png");
	mTextureHolder.load(ID::RockSmall, "images/rock_small.png");
	mTextureHolder.load(ID::BulletBlue, "images/fire_blue.png");
	mTextureHolder.load(ID::Spaceship, "images/spaceship.png");
	mTextureHolder.load(ID::SpaceshipFly, "images/spaceship.png");
	mTextureHolder.load(ID::ExplosionShip, "images/type_B.png");
	mTextureHolder.load(ID::SpaceBackground, "images/background.jpg");
	mTextureHolder.load(ID::Wall, "images/wall.png");

	sBackground.setTexture(mTextureHolder.getResource(ID::SpaceBackground));

	mAnimationHolder.load(ID::Explosion, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::Explosion), sf::Vector2f(0, 0), 256, 256, 48, 0.5f));

	mAnimationHolder.load(ID::RockBig, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::RockBig), sf::Vector2f(0, 0), 64, 64, 16, 0.2f));

	mAnimationHolder.load(ID::RockSmall, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::RockSmall), sf::Vector2f(0, 0), 64, 64, 16, 0.2f));

	mAnimationHolder.load(ID::BulletBlue, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::BulletBlue), sf::Vector2f(0, 0), 32, 64, 16, 0.8f));

	mAnimationHolder.load(ID::Spaceship, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::Spaceship), sf::Vector2f(40, 0), 40, 40, 1, 0.f));

	mAnimationHolder.load(ID::SpaceshipFly, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::SpaceshipFly), sf::Vector2f(40, 40), 40, 40, 1, 0.f));

	mAnimationHolder.load(ID::ExplosionShip, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::ExplosionShip), sf::Vector2f(0, 0), 192, 192, 64, 0.5f));

	mAnimationHolder.load(ID::Wall, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::Wall), sf::Vector2f(0, 0), 50, 50, 1, 0.f));

	mSoundHolder.load(ID::BigExplosionSound, "sounds/explosion_big.wav");
	mSoundHolder.load(ID::SmallExplosionSound, "sounds/explosion_small.wav");
	mSoundHolder.load(ID::BulletBlueSound, "sounds/laser_blue.wav");
}

/**
 * Builds game scene. Player, enemies etc...
 */
void GamePlay::buildScene()
{
	// Create Map
	addWalls();

	// Create Player
	createPlayer();

	// Create Big Asteroids
	createAsteroids(ID::RockBig, 15);

	// Create Small Asteroids
	createAsteroids(ID::RockSmall, 10);
}

/**
 * Creates walls
 */
void GamePlay::addWalls()
{
	for (int i = 0; i < 24; ++i)
		for (int j = 0; j < 39; ++j)
			if (generator.getField(static_cast<uint32_t>(j), static_cast<uint32_t>(i)) == MapField::Wall)
				entities.push_back(std::make_unique<Wall>(
					this, mAnimationHolder.getResource(ID::Wall), sf::Vector2f(static_cast<float>(j * 50), static_cast<float>(i * 50)), 0.F, 25.F));
}

/**
 * Creates Player's aircraft
 */
void GamePlay::createPlayer()
{
	auto player = std::make_unique<Player>(this, mAnimationHolder.getResource(ID::Spaceship), generator.getStartPoint(), 0.F, 20.F);
	playerAircraft = player.get();
	entities.push_back(std::move(player));
}

void GamePlay::createAsteroids(ID asteroidId, const uint32_t& count)
{
	float radius{};
	float angle{};
	sf::Vector2f pos{};

	for (uint32_t i = 0; i < count; ++i)
	{
		// Set Position
		pos.x = static_cast<float>(randDist(mt) % worldDimension.x);
		pos.y = static_cast<float>(randDist(mt) % worldDimension.y);

		// Set Radius
		if (asteroidId == ID::RockSmall)
			radius = 15.f;
		else if (asteroidId == ID::RockBig)
			radius = 25.f;

		// Set Angle
		angle = static_cast<float>(randDist(mt) % 360);

		// Spawn Asteroid
		if (canSpawn(pos.x, pos.y, radius))
			entities.push_back(std::make_unique<Asteroid>(this, mAnimationHolder.getResource(asteroidId), pos, angle, radius));
		else
			continue;
	}
}

void GamePlay::checkRandomAsteroid()
{
	uint32_t rand = randDist(mt) % 300;
	if (rand == 150)
		createAsteroids(ID::RockBig, 1);
	else if (rand == 149)
		createAsteroids(ID::RockSmall, 1);
}

/**
 * Checks if players wants to move
 */
void GamePlay::checkPlayerMove()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) playerAircraft->rotate(3.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) playerAircraft->rotate(-3.f);
	playerAircraft->setMoving(sf::Keyboard::isKeyPressed(sf::Keyboard::Up));

	if (playerAircraft->isMoving())
		playerAircraft->setAnimation(mAnimationHolder.getResource(ID::SpaceshipFly));
	else
		playerAircraft->setAnimation(mAnimationHolder.getResource(ID::Spaceship));
}

/**
 * Checks Entities collisions.
 */
void GamePlay::checkCollisions()
{
	for (auto& a : entities)
	{
		for (auto& b : entities)
		{
			if (a->getId() == EntityId::Asteroid && b->getId() == EntityId::Bullet && isCollide(a.get(), b.get()))
				asteroidVsBullet(a.get(), b.get());
			else if (a->getId() == EntityId::Player && b->getId() == EntityId::Asteroid && isCollide(a.get(), b.get()))
				playerVsAsteroid(a.get(), b.get());
			else if (a->getId() == EntityId::Player && b->getId() == EntityId::Wall && isCollide(a.get(), b.get()))
				playerVsWall(a.get(), b.get());
			else if (a->getId() == EntityId::Asteroid && b->getId() == EntityId::Wall && isCollide(a.get(), b.get()))
				makeBounce(a.get(), b.get());
			else if (a->getId() == EntityId::Asteroid && b->getId() == EntityId::Asteroid && isCollide(a.get(), b.get()) && a != b)
				 makeBounce(a.get(), b.get());
			else if (a->getId() == EntityId::Bullet && b->getId() == EntityId::Wall && isCollide(a.get(), b.get()))
				a->setLife(false);
		}
	}
}

/**
 * Updates Entities and their animation. Remove them if not alive.
 */
void GamePlay::checkUpdateEntities(float dt)
{
	auto end = entities.end();
	for (auto i = entities.begin(); i != end;)
	{
		// Get Entity
		auto e = i->get();

		// Update Move
		e->update(dt);

		// Update Animation
		e->getAnimation().update();

		// Remove Explosion if finished playing
		if (e->getId() == EntityId::Explosion && e->getAnimation().finished())
			e->setLife(false);

		// Erase dead objects
		if (!e->getLife())
			i = entities.erase(i);
		else
			++i;
	}
}

/**
 * Checks Game sounds. If stopped playing - remove them.
 */
void GamePlay::checkSounds()
{
	auto end = qSounds.end();
	for (auto i = qSounds.begin(); i != end;)
	{
		if (i->getStatus() == sf::Sound::Stopped)
			i = qSounds.erase(i);
		else
			++i;
	}
}

/**
 * Checks if there was collision between two entities
 * @param a first entity
 * @param b second entity
 * @return true - if there was collision, false - otherwise
 */
bool GamePlay::isCollide(const Entity* const a, const Entity* const b)
{
	return (b->getPosition().x - a->getPosition().x) * (b->getPosition().x - a->getPosition().x) +
		(b->getPosition().y - a->getPosition().y) * (b->getPosition().y - a->getPosition().y) <
		(a->getRadius() + b->getRadius()) * (a->getRadius() + b->getRadius());
}

void GamePlay::makeBounce(Entity* const a, Entity* const b)
{
	// Current Velocity Vector
	float vX = a->getVelocity().x;
	float vY = a->getVelocity().y;

	// Velocity Vector Norm
	float vLen = static_cast<float>(sqrt(vX*vX + vY*vY));

	// Normal Line
	float nX = b->getPosition().x - a->getPosition().x;
	float nY = b->getPosition().y - a->getPosition().y;

	// Normalize N - vector
	float nLen = static_cast<float>(sqrt(nX * nX + nY * nY));
	nX /= nLen;
	nY /= nLen;

	// V * N - dot product
	float dotProd_VN = vX * nX + vY * nY;

	// New V vector
	float nVX = vX - 2 * dotProd_VN * nX;
	float nVY = vY - 2 * dotProd_VN * nY;

	a->setVelocity(nVX, nVY);
}

void GamePlay::asteroidVsBullet(Entity* const a, Entity* const b)
{
	a->setLife(false);
	b->setLife(false);

	// Play Sound
	if (a->getRadius() > 20.f)
		qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BigExplosionSound)));
	else
		qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::SmallExplosionSound)));
	qSounds.back().play();

	entities.push_back(std::make_unique<Explosion>(
		this, mAnimationHolder.getResource(ID::Explosion), sf::Vector2f(a->getPosition().x, a->getPosition().y), 0.f, 0.f));
}

void GamePlay::playerVsAsteroid(Entity* const a, Entity* const b)
{
	b->setLife(false);
	entities.push_back(std::make_unique<Explosion>(this, mAnimationHolder.getResource(ID::ExplosionShip),
		sf::Vector2f(a->getPosition().x, a->getPosition().y), 0.f, 0.f));

	qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BigExplosionSound)));
	qSounds.back().play();

	playerAircraft->setPosition(200.f, 200.f);
	playerAircraft->setVelocity(0.f, 0.f);
}

void GamePlay::playerVsWall(Entity* const a, Entity* const b)
{
	entities.push_back(std::make_unique<Explosion>(this, mAnimationHolder.getResource(ID::ExplosionShip),
		sf::Vector2f(a->getPosition().x, a->getPosition().y), 0.f, 0.f));

	qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BigExplosionSound)));
	qSounds.back().play();

	playerAircraft->setPosition(200.f, 200.f);
	playerAircraft->setVelocity(0.f, 0.f);
}

bool GamePlay::canSpawn(const float& x, const float& y, const float& radius)
{
	return generator.isEmpty(x, y) && generator.isEmpty(x - radius, y - radius) && generator.isEmpty(x, y - radius) &&
		generator.isEmpty(x + radius, y - radius) && generator.isEmpty(x - radius, y) && generator.isEmpty(x + radius, y) &&
		generator.isEmpty(x + radius, y + radius) && generator.isEmpty(x, y + radius) &&
		generator.isEmpty(x - radius, y + radius);
}
