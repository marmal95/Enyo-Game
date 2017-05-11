#include "MapGenerator.h"
#include "Explosion.h"
#include "GamePlay.h"
#include "Constants.h"

#include <SFML/Window/Event.hpp>

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
	qSounds(), wallVec(), exploVec(), asteroidVec(), bulletVec(), sBackground(),
	// Map Generator
	generator(WALL_COUNT_W, WALL_COUNT_H, "z", 1),
	// Random Generator
	mt(std::random_device()()), randDist(),
	// Scores
	scorePoints{}
{
	wallVec.reserve(300);
	exploVec.reserve(30);
	asteroidVec.reserve(50);
	bulletVec.reserve(50);
}

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
	updateEntities(dt);
	checkRandomAsteroid();

	checkSounds();
	updateText();

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
	for (const auto& i : wallVec)
		window.draw(i);

	for (const auto& i : exploVec)
		window.draw(i);

	for (const auto& i : asteroidVec)
		window.draw(i);

	for (const auto& i : bulletVec)
		window.draw(i);

	window.draw(*playerAircraft.get());
	window.draw(scoreText);
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
				bulletVec.emplace_back(mAnimationHolder.getResource(ID::BulletBlue),
					Vector<float>(playerAircraft->getPosition().x, playerAircraft->getPosition().y), playerAircraft->getRotation(), BULLET_RADIUS);

				qSounds.emplace_back(mSoundHolder.getResource(ID::BulletBlueSound));
				qSounds.back().play();
			}
			break;

		case sf::Keyboard::LControl:
			if (pressed)
			{
				float x = 30 * cos(playerAircraft->getRotation()* M_PI / 180.F) - 30 * sin(playerAircraft->getRotation()* M_PI / 180.F);
				float y = 30 * sin(playerAircraft->getRotation()* M_PI / 180.F) + 30 * cos(playerAircraft->getRotation()* M_PI / 180.F);

				bulletVec.emplace_back(mAnimationHolder.getResource(ID::BulletRed),
					Vector<float>(x,y), playerAircraft->getRotation(), BULLET_RADIUS);
				bulletVec.back().move(playerAircraft->getPosition());

				x = 30 * cos(playerAircraft->getRotation()* M_PI / 180.F) + 30 * sin(playerAircraft->getRotation()* M_PI / 180.F);
				y = 30 * sin(playerAircraft->getRotation()* M_PI / 180.F) - 30 * cos(playerAircraft->getRotation()* M_PI / 180.F);
				bulletVec.emplace_back(mAnimationHolder.getResource(ID::BulletRed),
					Vector<float>(x,y), playerAircraft->getRotation(), BULLET_RADIUS);
				bulletVec.back().move(playerAircraft->getPosition());

				qSounds.emplace_back(mSoundHolder.getResource(ID::BulletRedSound));
				qSounds.back().play();
			}
			break;

		default:
			break;
	}
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
	mTextureHolder.load(ID::BulletRed, "images/fire_red.png");
	mTextureHolder.load(ID::Spaceship, "images/spaceship2.png", true);
	mTextureHolder.load(ID::SpaceshipFly, "images/spaceship2_fly.png");
	mTextureHolder.load(ID::ExplosionShip, "images/type_B.png");
	mTextureHolder.load(ID::SpaceBackground, "images/background.jpg");
	mTextureHolder.load(ID::Wall, "images/wall.png");

	sBackground.setTexture(mTextureHolder.getResource(ID::SpaceBackground));

	mAnimationHolder.load(ID::Explosion, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::Explosion), EXPLO_WIDTH, EXPLO_HEIGHT, 48, 0.5f));

	mAnimationHolder.load(ID::RockBig, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::RockBig), ROCK_WIDTH, ROCK_HEIGHT, 16, 0.2f));

	mAnimationHolder.load(ID::RockSmall, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::RockSmall), ROCK_WIDTH, ROCK_HEIGHT, 16, 0.2f));

	mAnimationHolder.load(ID::BulletBlue, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::BulletBlue), BULLET_WIDTH, BULLET_HEIGHT, 16, 0.8f));

	mAnimationHolder.load(ID::BulletRed, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::BulletRed), BULLET_WIDTH, BULLET_HEIGHT, 16, 0.8f));

	mAnimationHolder.load(ID::Spaceship, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::Spaceship),  SHIP_WIDTH, SHIP_HEIGHT, 1, 0.f));

	mAnimationHolder.load(ID::SpaceshipFly, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::SpaceshipFly), SHIP_WIDTH, SHIP_HEIGHT, 1, 0.f));

	mAnimationHolder.load(ID::ExplosionShip, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::ExplosionShip), SHIP_EXPLOT_WIDTH, SHIP_EXPLOT_HEIGHT, 64, 0.5f));

	mAnimationHolder.load(ID::Wall, std::make_unique<Animation>(
		mTextureHolder.getResource(ID::Wall), WALL_WIDTH, WALL_HEIGHT, 1, 0.f));

	mSoundHolder.load(ID::BigExplosionSound, "sounds/explosion_big.wav");
	mSoundHolder.load(ID::SmallExplosionSound, "sounds/explosion_small.wav");
	mSoundHolder.load(ID::BulletBlueSound, "sounds/laser_blue.wav");
	mSoundHolder.load(ID::BulletRedSound, "sounds/laser_red.wav");

	if (!mFont.loadFromFile("fonts/cosmic_cube.ttf"))
		throw std::runtime_error("Could not find font \"cosmic_cube.ttf\"");
	scoreText.setFont(mFont);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setString("0");
	scoreText.setPosition(20, 20);
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
	createAsteroids(ID::RockSmall, 15);
}

/**
 * Creates walls
 */
void GamePlay::addWalls()
{
	for (uint32_t i = 0; i < WALL_COUNT_H; ++i)
		for (uint32_t j = 0; j < WALL_COUNT_W; ++j)
			if (generator.getField(j, i) == MapField::Wall)
				wallVec.emplace_back(mAnimationHolder.getResource(ID::Wall), 
					Vector<float>(static_cast<float>(j * WALL_WIDTH),static_cast<float>(i * WALL_HEIGHT)), 0.F, WALL_RADIUS);
}

/**
 * Creates Player's aircraft
 */
void GamePlay::createPlayer()
{
	playerAircraft = std::make_unique<Player>(mAnimationHolder.getResource(ID::Spaceship), generator.getStartPoint(), 0.F, SHIP_RADIUS);
}

void GamePlay::createAsteroids(ID asteroidId, const uint32_t& count)
{
	float radius{};
	float angle{};
	Vector<float> pos{};

	for (uint32_t i = 0; i < count; ++i)
	{
		// Set Position
		pos.x = static_cast<float>(randDist(mt) % worldDimension.x);
		pos.y = static_cast<float>(randDist(mt) % worldDimension.y);

		// Set Radius
		if (asteroidId == ID::RockSmall)
			radius = SMALL_ROCK_RADIUS;
		else if (asteroidId == ID::RockBig)
			radius = BIG_ROCK_RADIUS;

		// Set Angle
		angle = static_cast<float>(randDist(mt) % 360);

		// Spawn Asteroid
		if (generator.canSpawn(pos.x, pos.y, radius))
			asteroidVec.emplace_back(mAnimationHolder.getResource(asteroidId), pos, angle, radius);
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
	// Asteroid Vs Asteroid
	for (auto& a : asteroidVec)
		for (auto& b : asteroidVec)
			if (&a != &b && isCollide(a, b))
				makeBounce(a, b);

	// Asteroid Vs Wall
	for (auto& a : asteroidVec)
		for (auto& b : wallVec)
			if(isCollide(a, b))
				makeBounce(a, b);

	// Asteroid Vs Bullet
	for (auto& a : asteroidVec)
		for (auto& b : bulletVec)
			if(isCollide(a, b))
				asteroidVsBullet(a, b);

	// Bullet Vs Wall
	for (auto& a : bulletVec)
		for (auto& b : wallVec)
			if(isCollide(a, b))
				a.setLife(false);

	// Player vs Asteroid
	for(auto& a : asteroidVec)
		if(isCollide(*playerAircraft.get(), a))
			playerVsAsteroid(*playerAircraft.get(), a);

	// Player vs Wall
	for (auto& a : wallVec)
		if (isCollide(*playerAircraft.get(), a))
			playerVsWall(*playerAircraft.get(), a);
}

/**
 * Updates Entities and their animation. Remove them if not alive.
 */
void GamePlay::updateEntities(float dt)
{
	playerAircraft->update(dt);
	playerAircraft->getAnimation().update();

	updateWalls(dt);
	updateExplosions(dt);
	updateAsteroids(dt);
	updateBullets(dt);
}

/**
 * Checks Game sounds. If stopped playing - remove them.
 */
void GamePlay::checkSounds()
{
	qSounds.remove_if([](auto& snd) {return snd.getStatus() == sf::Sound::Stopped; });
}

void GamePlay::updateWalls(float dt)
{
	for (auto i = wallVec.begin(); i != wallVec.end();)
	{
		i->update(dt);
		i->getAnimation().update();

		if (!i->getLife())
		{
			std::iter_swap(i, wallVec.end() -1);
			wallVec.erase(wallVec.end() - 1);
		}
		else
			++i;
	}
}

void GamePlay::updateExplosions(float dt)
{
	for (auto i = exploVec.begin(); i != exploVec.end();)
	{
		i->update(dt);
		i->getAnimation().update();

		if (i->getAnimation().finished())
			i->setLife(false);

		if (!i->getLife())
		{
			std::iter_swap(i, exploVec.end() -1);
			exploVec.erase(exploVec.end() - 1);
		}
		else
			++i;
	}
}

void GamePlay::updateAsteroids(float dt)
{
	for (auto i = asteroidVec.begin(); i != asteroidVec.end();)
	{
		i->update(dt);
		i->getAnimation().update();

		if (!i->getLife())
		{
			std::iter_swap(i, asteroidVec.end() -1);
			asteroidVec.erase(asteroidVec.end() - 1);
		}
		else
			++i;
	}
}

void GamePlay::updateBullets(float dt)
{
	for (auto i = bulletVec.begin(); i != bulletVec.end();)
	{
		i->update(dt);
		i->getAnimation().update();

		if (!i->getLife())
		{
			std::iter_swap(i, bulletVec.end() -1);
			bulletVec.erase(bulletVec.end() - 1);
		}
		else
			++i;
	}
}

void GamePlay::updateText()
{
	auto viewSize = mWorldView.getSize();
	auto playerPos = playerAircraft->getPosition();
	scoreText.setPosition(playerPos.x - viewSize.x / 2 + 20, playerPos.y - viewSize.y / 2 + 20);
}

/**
 * Checks if there was collision between two entities
 * @param a first entity
 * @param b second entity
 * @return true - if there was collision, false - otherwise
 */
bool GamePlay::isCollide(const Entity& a, const Entity& b)
{
	return (b.getPosition().x - a.getPosition().x) * (b.getPosition().x - a.getPosition().x) +
		(b.getPosition().y - a.getPosition().y) * (b.getPosition().y - a.getPosition().y) <
		(a.getRadius() + b.getRadius()) * (a.getRadius() + b.getRadius());
}

void GamePlay::makeBounce(Entity& a, Entity& b)
{
	// Current Velocity Vector
	Vector<float> vel = a.getVelocity();

	// Normal Vector
	Vector<float> normVec = b.getPosition() - a.getPosition();

	// Normalize Normal - vector
	normVec.normalize();

	// Velocity and Normal dot product
	float dotProd_VN = vel * normVec;

	// New Velocity vector
	vel -= 2.f * dotProd_VN * normVec;

	a.setVelocity(vel);
}

void GamePlay::asteroidVsBullet(Entity& a, Entity& b)
{
	a.setLife(false);
	b.setLife(false);

	// Play Sound
	if (a.getId() == EntityId::BigAsteroid)
		qSounds.emplace_back(mSoundHolder.getResource(ID::BigExplosionSound));
	else if(a.getId() == EntityId::SmallAsteroid)
		qSounds.emplace_back(mSoundHolder.getResource(ID::SmallExplosionSound));
	qSounds.back().play();

	exploVec.emplace_back(
		mAnimationHolder.getResource(ID::Explosion), Vector<float>(a.getPosition().x, a.getPosition().y), 0.f, EXPLO_RADIUS);

	++scorePoints;
	scoreText.setString(std::to_string(scorePoints));
}

void GamePlay::playerVsAsteroid(Entity& a, Entity& b)
{
	b.setLife(false);
	exploVec.emplace_back(mAnimationHolder.getResource(ID::ExplosionShip),
		Vector<float>(a.getPosition().x, a.getPosition().y), 0.f, EXPLO_RADIUS);

	qSounds.emplace_back(mSoundHolder.getResource(ID::BigExplosionSound));
	qSounds.back().play();

	playerAircraft->setPosition(generator.getStartPoint());
	playerAircraft->setVelocity(0.f, 0.f);
}

void GamePlay::playerVsWall(Entity& a, Entity& b)
{
	exploVec.emplace_back(mAnimationHolder.getResource(ID::ExplosionShip),
		Vector<float>(a.getPosition().x, a.getPosition().y), 0.f, EXPLO_RADIUS);

	qSounds.emplace_back(mSoundHolder.getResource(ID::BigExplosionSound));
	qSounds.back().play();

	playerAircraft->setPosition(generator.getStartPoint());
	playerAircraft->setVelocity(0.f, 0.f);
}
