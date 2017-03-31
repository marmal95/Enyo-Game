#include "World.h"
#include "Asteroid.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Wall.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Window/Event.hpp>

World::World(sf::RenderWindow & window, const sf::Vector2i& dimension)
	: worldDimension(dimension), mWindow(window), mWorldView(window.getDefaultView()),
	mTextureHolder(), mAnimationHolder(), mSoundHolder(),
	qSounds(), entities(), sBackground(),
	generator(39,24,"z",1)
{
	initializeWold();
	buildScene();
	addWalls();
}

void World::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();

		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::Space)
			{
				entities.push_back(
					std::make_unique<Bullet>(this, mAnimationHolder.getResource(ID::BulletBlue), sf::Vector2f(playerAircraft->getPosition().x,
						playerAircraft->getPosition().y), playerAircraft->getRotation(), 10.F));
				qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BulletBlueSound)));
				qSounds.back().play();
			}
	}
}

void World::update()
{
	checkPlayerMove();
	checkCollisions();
	checkUpdateEntities();
	checkSounds();
}

void World::draw()
{
	mWorldView.setCenter(playerAircraft->getPosition());
	mWindow.setView(mWorldView);

	// Draw Background
	mWindow.draw(sBackground);

	// Draw all entities
	for (const auto& i : entities)
		mWindow.draw(*i);
}

sf::Vector2i World::getDimension() const
{
	return worldDimension;
}

void World::initializeWold()
{
	mTextureHolder.load(ID::Explosion, "images/type_C.png");
	mTextureHolder.load(ID::RockBig, "images/rock.png");
	mTextureHolder.load(ID::RockSmall, "images/rock_small.png");
	mTextureHolder.load(ID::BulletBlue, "images/fire_blue.png");
	mTextureHolder.load(ID::Spaceship, "images/spaceship.png", true);
	mTextureHolder.load(ID::SpaceshipFly, "images/spaceship.png");
	mTextureHolder.load(ID::ExplosionShip, "images/type_B.png");
	mTextureHolder.load(ID::SpaceBackground, "images/background.jpg", true);
	mTextureHolder.load(ID::Wall, "images/wall.png");

	sBackground.setTexture(mTextureHolder.getResource(ID::SpaceBackground));

	mAnimationHolder.load(ID::Explosion, std::make_unique<Animation>(mTextureHolder.getResource(ID::Explosion), sf::Vector2f(0, 0), 256, 256, 48, 0.5));
	mAnimationHolder.load(ID::RockBig, std::make_unique<Animation>(mTextureHolder.getResource(ID::RockBig), sf::Vector2f(0, 0), 64, 64, 16, 0.2));
	mAnimationHolder.load(ID::RockSmall, std::make_unique<Animation>(mTextureHolder.getResource(ID::RockSmall), sf::Vector2f(0, 0), 64, 64, 16, 0.2));
	mAnimationHolder.load(ID::BulletBlue, std::make_unique<Animation>(mTextureHolder.getResource(ID::BulletBlue), sf::Vector2f(0, 0), 32, 64, 16, 0.8));
	mAnimationHolder.load(ID::Spaceship, std::make_unique<Animation>(mTextureHolder.getResource(ID::Spaceship), sf::Vector2f(40, 0), 40, 40, 1, 0));
	mAnimationHolder.load(ID::SpaceshipFly, std::make_unique<Animation>(mTextureHolder.getResource(ID::SpaceshipFly), sf::Vector2f(40, 40), 40, 40, 1, 0));
	mAnimationHolder.load(ID::ExplosionShip, std::make_unique<Animation>(mTextureHolder.getResource(ID::ExplosionShip), sf::Vector2f(0, 0), 192, 192, 64, 0.5));
	mAnimationHolder.load(ID::Wall, std::make_unique<Animation>(mTextureHolder.getResource(ID::Wall), sf::Vector2f(0, 0), 50, 50, 1, 0));

	mSoundHolder.load(ID::BigExplosionSound, "sounds/explosion_big.wav");
	mSoundHolder.load(ID::SmallExplosionSound, "sounds/explosion_small.wav");
	mSoundHolder.load(ID::BulletBlueSound, "sounds/laser_blue.wav");
}

void World::buildScene()
{
	// Create Map
	// ...

	// Create Player
	createPlayer();

	// Create Bigger Asteroids in Random positions
	createAsteroids(15);
	
	// Create Smaller Asteroids in Random positions
	createSmallAsteroids(5);
}

void World::addWalls()
{
	for (int i = 0; i < 24; ++i)
		for (int j = 0; j < 39; ++j)
			if (generator.getField(j, i) == MapField::Wall)
				entities.push_back(
					std::make_unique<Wall>(this, mAnimationHolder.getResource(ID::Wall),
						sf::Vector2f(static_cast<float>(j * 50), static_cast<float>(i * 50)), 0, 25));
}

void World::createPlayer()
{
	auto player = std::make_unique<Player>(this, mAnimationHolder.getResource(ID::Spaceship), sf::Vector2f(200.F, 200.F), 0.F, 20.F);
	playerAircraft = player.get();
	entities.push_back(std::move(player));
}

void World::createAsteroids(const uint32_t & count)
{
	float x,y;
	for (uint32_t i = 0; i < count; ++i)
	{
		x = static_cast<float>(rand() % worldDimension.x);
		y = static_cast<float>(rand() % worldDimension.y);
		//to be sure that asteroid will not hit wall
		if(generator.isEmpty(x, y) && generator.isEmpty(x+25.F, y+25.F))
			entities.push_back(
			std::make_unique<Asteroid>(this, mAnimationHolder.getResource(ID::RockBig),
				sf::Vector2f(x , y), static_cast<float>(rand() % 360), 25.F));
		else
			--i;//to create count asteroids
	}
}

void World::createSmallAsteroids(const uint32_t & count)
{
	for (uint32_t i = 0; i < count; ++i)
		entities.push_back(
			std::make_unique<Asteroid>(this, mAnimationHolder.getResource(ID::RockSmall),
				sf::Vector2f(
					static_cast<float>(rand() % worldDimension.x),
					static_cast<float>(rand() % worldDimension.y)),
					static_cast<float>(rand() % 360), 15.F));
}


void World::checkPlayerMove()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) playerAircraft->rotate(3);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) playerAircraft->rotate(-3);
	playerAircraft->setMoving(sf::Keyboard::isKeyPressed(sf::Keyboard::Up));

	if (playerAircraft->isMoving())
		playerAircraft->setAnimation(mAnimationHolder.getResource(ID::SpaceshipFly));
	else
		playerAircraft->setAnimation(mAnimationHolder.getResource(ID::Spaceship));
}

void World::checkCollisions()
{
	for (auto& a : entities)
	{
		for (auto& b : entities)
		{
			if (a->getName() == "Asteroid" && b->getName() == "Bullet" && isCollide(a.get(), b.get()))
			{
				a->setLife(false);
				b->setLife(false);

				// Play Sound
				if (a->getRadius() > 20)
					qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BigExplosionSound)));
				else
					qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::SmallExplosionSound)));
				qSounds.back().play();

				entities.push_back(std::make_unique<Explosion>(this, mAnimationHolder.getResource(ID::Explosion),
					sf::Vector2f(a->getPosition().x, a->getPosition().y)));

				for (int i = 0; i < 2; i++)
				{
					if (a->getRadius() == 15)
						break;
					entities.push_back(
						std::make_unique<Asteroid>(this, mAnimationHolder.getResource(ID::RockSmall),
							sf::Vector2f(a->getPosition().x, a->getPosition().y), rand() % 360, 15));
				}
			}
			else if (a->getName() == "Player" && b->getName() == "Asteroid" && isCollide(a.get(), b.get()))
			{
				b->setLife(false);
				entities.push_back(std::make_unique<Explosion>(this, mAnimationHolder.getResource(ID::ExplosionShip),
					sf::Vector2f(a->getPosition().x, a->getPosition().y)));

				qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BigExplosionSound)));
				qSounds.back().play();

				playerAircraft->setPosition(200, 200);
				playerAircraft->setVolocity(0, 0);
			}
			else if (a->getName() == "Player" && b->getName() == "Wall" && isCollide(a.get(), b.get()))
			{
				entities.push_back(std::make_unique<Explosion>(this, mAnimationHolder.getResource(ID::ExplosionShip),
					sf::Vector2f(a->getPosition().x, a->getPosition().y)));

				qSounds.push_back(sf::Sound(mSoundHolder.getResource(ID::BigExplosionSound)));
				qSounds.back().play();

				playerAircraft->setPosition(200, 200);
				playerAircraft->setVolocity(0, 0);
			}
			else if (a->getName() == "Asteroid" && b->getName() == "Wall" && isCollide(a.get(), b.get()))
			{
				a->setVolocity(a->getVolocity().x*-1, a->getVolocity().y*-1);
			}
			else if (a->getName() == "Bullet" && b->getName() == "Wall" && isCollide(a.get(), b.get()))
			{
				a->setLife(false);
			}
		}
	}
}

void World::checkUpdateEntities()
{
	auto end = entities.end();
	for (auto i = entities.begin(); i != end;)
	{
		// Get Entity
		auto e = i->get();

		// Update Move
		e->update();

		// Update Animation
		e->getAnimation().update();

		// Remove Explosion if finished playing
		if (e->getName() == "Explosion" && e->getAnimation().finished())
			e->setLife(0);

		// Erase dead objects
		if (!e->getLife())
			i = entities.erase(i);
		else
			++i;
	}
}

void World::checkSounds()
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

bool World::isCollide(const Entity * const a, const Entity * const b)
{
	if (a->getName() == "Wall")
	{
		float circleDistX = abs(b->getPosition().x - a->getPosition().x);
		float circleDistY = abs(b->getPosition().y - a->getPosition().y);

		if (circleDistX > (a->getRadius() / 2 + b->getRadius()))
			return false;
		if (circleDistY > (a->getRadius() / 2 + b->getRadius()))
			return false;

		if (circleDistX <= (a->getRadius() / 2))
			return true;
		if (circleDistY <= (a->getRadius() / 2))
			return true;

		float cornerDistance = (circleDistX - a->getRadius() / 2)*(circleDistX - a->getRadius() / 2) +
			(circleDistY - a->getRadius() / 2)*(circleDistY - a->getRadius() / 2);
		return (cornerDistance <= b->getRadius()*b->getRadius());
	}
	else
		return (b->getPosition().x - a->getPosition().x) * (b->getPosition().x - a->getPosition().x) +
		(b->getPosition().y - a->getPosition().y) * (b->getPosition().y - a->getPosition().y) <
		(a->getRadius() + b->getRadius()) * (a->getRadius() + b->getRadius());
}
