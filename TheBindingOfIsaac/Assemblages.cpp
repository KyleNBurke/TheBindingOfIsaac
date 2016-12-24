#include "stdafx.h"
#include "Assemblages.hpp"
#include "PlayerControlledCom.hpp"
#include "VelocityCom.hpp"
#include "AccelerationCom.hpp"
#include "PitCollisionCom.hpp"
#include "WallCollisionCom.hpp"
#include "ProjectileCom.hpp"
#include "HealthCom.hpp"
#include "PlayerShotCom.hpp"
#include "BouncerCom.hpp"
#include "LifetimeCom.hpp"
#include "AnimationCom.hpp"
#include "AnimationStateStatic.hpp"
#include "AnimationStateDynamic.hpp"
#include "PacMoveCom.hpp"
#include "JimmyMoveCom.hpp"
#include "JimmyShotCom.hpp"
#include "ItemCom.hpp"

Assemblages::Assemblages() {}

Assemblages& Assemblages::getInstance()
{
	static Assemblages instance;
	return instance;
}

void Assemblages::initialize()
{
	playerSpriteSheet.loadFromFile("Resources/Player.png");
	projectilesSpriteSheet.loadFromFile("Resources/Projectiles.png");
	enemySpriteSheet.loadFromFile("Resources/Enemies.png");
	particleSpriteSheet.loadFromFile("Resources/Particles.png");
	itemsSpriteSheet.loadFromFile("Resources/Items.png");
}

#pragma region Draw Priorities
/*
room floor
0 stains & deaths
1 projectiles
2 enemies
*/

#pragma endregion

Entity Assemblages::createPlayer(sf::Vector2f position)
{
	Entity player(sf::Sprite(playerSpriteSheet, sf::IntRect(0, 0, 7, 6)), position, sf::IntRect(1, 1, 5, 4), 1);

	player.addComponent(std::unique_ptr<Component>(new PlayerControlledCom(500.0f, 0.1f)));
	player.addComponent(std::unique_ptr<Component>(new VelocityCom()));
	player.addComponent(std::unique_ptr<Component>(new AccelerationCom()));
	player.addComponent(std::unique_ptr<Component>(new PitCollisionCom()));
	player.addComponent(std::unique_ptr<Component>(new WallCollisionCom()));
	player.addComponent(std::unique_ptr<Component>(new PlayerShotCom()));
	player.addComponent(std::unique_ptr<Component>(new HealthCom(5)));

	return player;
}

Entity Assemblages::createPlayerDamageStain(sf::Vector2f position)
{
	int x = std::rand() % 3;

	Entity stain(sf::Sprite(playerSpriteSheet, sf::IntRect(4 * x, 7, 4, 4)), position, 0);

	return stain;
}

Entity Assemblages::createPlayerProjectile(sf::Vector2f position, sf::Vector2f velocity)
{
	Entity projectile(sf::Sprite(projectilesSpriteSheet, sf::IntRect(0, 0, 4, 4)), position, sf::IntRect(1, 1, 2, 2), 1);

	projectile.addComponent(std::unique_ptr<Component>(new VelocityCom(velocity)));
	projectile.addComponent(std::unique_ptr<Component>(new ProjectileCom(ProjectileCom::ProjectileType::Player, ProjectileCom::ProjectileVariation::Regular)));
	projectile.addComponent(std::unique_ptr<Component>(new LifetimeCom(0.5f)));

	return projectile;
}

Entity Assemblages::createPlayerBomb(sf::Vector2f position)
{
	Entity bomb(sf::Sprite(projectilesSpriteSheet, sf::IntRect(0, 8, 6, 8)), position, 1);

	bomb.addComponent(std::unique_ptr<Component>(new ProjectileCom(ProjectileCom::ProjectileType::Player, ProjectileCom::ProjectileVariation::Bomb)));
	bomb.addComponent(std::unique_ptr<Component>(new LifetimeCom(1.0f)));

	std::unique_ptr<AnimationStateDynamic> bombState(new AnimationStateDynamic(sf::IntRect(0, 8, 6, 8), 2, 0.1f));
	std::unique_ptr<AnimationCom> animationCom(new AnimationCom());
	animationCom->states.push_back(std::move(bombState));
	bomb.addComponent(std::move(animationCom));

	return bomb;
}

Entity Assemblages::createRegularProjectile(sf::Vector2f position, sf::Vector2f velocity)
{
	Entity projectile(sf::Sprite(projectilesSpriteSheet, sf::IntRect(0, 4, 4, 4)), position, sf::IntRect(1, 1, 2, 2), 1);

	projectile.addComponent(std::unique_ptr<Component>(new VelocityCom(velocity)));
	projectile.addComponent(std::unique_ptr<Component>(new ProjectileCom(ProjectileCom::ProjectileType::Enemy, ProjectileCom::ProjectileVariation::Regular)));
	projectile.addComponent(std::unique_ptr<Component>(new LifetimeCom(1.0f)));

	return projectile;
}

Entity Assemblages::createBouncer(sf::Vector2f position, sf::Vector2f direction)
{
	Entity bouncer(sf::Sprite(enemySpriteSheet, sf::IntRect(0, 7, 8, 8)), position, sf::IntRect(1, 1, 6, 6), 1);

	bouncer.addComponent(std::unique_ptr<Component>(new VelocityCom(direction * 200.0f)));
	bouncer.addComponent(std::unique_ptr<Component>(new WallCollisionCom()));
	bouncer.addComponent(std::unique_ptr<Component>(new BouncerCom()));
	bouncer.addComponent(std::unique_ptr<Component>(new HealthCom(3)));

	return bouncer;
}

Entity Assemblages::createParticle(sf::Vector2f position, sf::IntRect textureRect, sf::Vector2f velocity, float lifetime)
{
	Entity particle(sf::Sprite(particleSpriteSheet, textureRect), position, 1);

	particle.addComponent(std::unique_ptr<Component>(new VelocityCom(velocity)));
	particle.addComponent(std::unique_ptr<Component>(new LifetimeCom(lifetime)));

	return particle;
}

Entity Assemblages::createPac(sf::Vector2f position, Direction initialDirection)
{
	Entity pac(sf::Sprite(enemySpriteSheet, sf::IntRect(0, 0, 6, 7)), position, sf::IntRect(1, 1, 5, 5), 2);

	sf::Vector2f vel;
	switch(initialDirection)
	{
		case Up:
			vel.y = -PacMoveCom::passiveSpeed;
			break;
		case Down:
			vel.y = PacMoveCom::passiveSpeed;
			break;
		case Left:
			vel.x = -PacMoveCom::passiveSpeed;
			break;
		case Right:
			vel.x = PacMoveCom::passiveSpeed;
			break;
	}

	pac.addComponent(std::unique_ptr<Component>(new VelocityCom(vel)));
	pac.addComponent(std::unique_ptr<Component>(new WallCollisionCom()));
	pac.addComponent(std::unique_ptr<Component>(new PitCollisionCom()));
	pac.addComponent(std::unique_ptr<Component>(new PacMoveCom(initialDirection)));
	pac.addComponent(std::unique_ptr<Component>(new HealthCom(5)));

	std::unique_ptr<AnimationStateStatic> passiveState(new AnimationStateStatic(sf::IntRect(0, 0, 6, 7)));
	std::unique_ptr<AnimationStateDynamic> aggressiveState(new AnimationStateDynamic(sf::IntRect(0, 0, 6, 7), 2, 0.1f));

	std::unique_ptr<AnimationCom> animationCom(new AnimationCom());
	animationCom->states.push_back(std::move(passiveState));
	animationCom->states.push_back(std::move(aggressiveState));

	pac.addComponent(std::move(animationCom));

	return pac;
}

Entity Assemblages::createJimmy(sf::Vector2f position)
{
	Entity jimmy(sf::Sprite(enemySpriteSheet, sf::IntRect(8, 7, 7, 7)), position, sf::IntRect(1, 1, 5, 5), 1);

	jimmy.addComponent(std::unique_ptr<Component>(new HealthCom(5)));
	jimmy.addComponent(std::unique_ptr<Component>(new VelocityCom()));
	jimmy.addComponent(std::unique_ptr<Component>(new AccelerationCom()));
	jimmy.addComponent(std::unique_ptr<Component>(new JimmyMoveCom(sf::Vector2f(position.x, position.y + 10.0f))));
	jimmy.addComponent(std::unique_ptr<Component>(new JimmyShotCom()));
	jimmy.addComponent(std::unique_ptr<Component>(new WallCollisionCom()));

	return jimmy;
}

Entity Assemblages::createEnemyDeath(sf::Vector2f position)
{
	Entity death(sf::Sprite(enemySpriteSheet, sf::IntRect(0, 0, 11, 11)), position, 0);

	const int frames = 8;
	const float frameTime = 0.08f;

	death.addComponent(std::unique_ptr<Component>(new LifetimeCom((float)frames * frameTime)));

	std::unique_ptr<AnimationStateDynamic> deathState(new AnimationStateDynamic(sf::IntRect(0, 22, 11, 11), frames, frameTime));
	std::unique_ptr<AnimationCom> animationCom(new AnimationCom());
	animationCom->states.push_back(std::move(deathState));
	death.addComponent(std::move(animationCom));

	return death;
}

Entity Assemblages::createEnemyDeathStain(sf::Vector2f position)
{
	int x = std::rand() % 2;

	Entity stain(sf::Sprite(enemySpriteSheet, sf::IntRect(9 * x, 34, 9, 9)), position,  0);

	return stain;
}

Entity Assemblages::createEnemyDamageStain(sf::Vector2f position)
{
	int x = std::rand() % 3;

	Entity stain(sf::Sprite(enemySpriteSheet, sf::IntRect(4 * x, 45, 4, 4)), position, 0);

	return stain;
}

Entity Assemblages::createProjectileDeath(sf::Vector2f position)
{
	Entity death(sf::Sprite(projectilesSpriteSheet, sf::IntRect(0, 0, 8, 8)), position, 0);

	const int frames = 4;
	const float frameTime = 0.1f;

	death.addComponent(std::unique_ptr<Component>(new LifetimeCom((float)frames * frameTime)));

	std::unique_ptr<AnimationStateDynamic> deathState(new AnimationStateDynamic(sf::IntRect(8, 0, 8, 8), frames, frameTime));
	std::unique_ptr<AnimationCom> animationCom(new AnimationCom());
	animationCom->states.push_back(std::move(deathState));
	death.addComponent(std::move(animationCom));

	return death;
}

Entity Assemblages::createBlockDestruction(sf::Vector2f position)
{
	Entity death(sf::Sprite(playerSpriteSheet, sf::IntRect(0, 0, 10, 10)), position, 0);

	const int frames = 5;
	const float frameTime = 0.1f;

	death.addComponent(std::unique_ptr<Component>(new LifetimeCom((float)frames * frameTime)));

	std::unique_ptr<AnimationStateDynamic> deathState(new AnimationStateDynamic(sf::IntRect(0, 12, 10, 10), frames, frameTime));
	std::unique_ptr<AnimationCom> animationCom(new AnimationCom());
	animationCom->states.push_back(std::move(deathState));
	death.addComponent(std::move(animationCom));

	return death;
}

Entity Assemblages::createExplosion(sf::Vector2f position)
{
	Entity explo(sf::Sprite(projectilesSpriteSheet, sf::IntRect(0, 0, 34, 32)), position, 1);

	const int frames = 12;
	const float frameTime = 0.04f;

	explo.addComponent(std::unique_ptr<Component>(new LifetimeCom((float)frames * frameTime)));

	std::unique_ptr<AnimationStateDynamic> exploState(new AnimationStateDynamic(sf::IntRect(0, 17, 34, 32), frames, frameTime));
	std::unique_ptr<AnimationCom> animationCom(new AnimationCom());
	animationCom->states.push_back(std::move(exploState));
	explo.addComponent(std::move(animationCom));

	return explo;
}

Entity Assemblages::createExplosionStain(sf::Vector2f position)
{
	Entity stain(sf::Sprite(projectilesSpriteSheet, sf::IntRect(0, 50, 11, 12)), position, 0);

	return stain;
}

Entity Assemblages::createROF_UpItem(sf::Vector2f position)
{
	Entity item(sf::Sprite(itemsSpriteSheet, sf::IntRect(0, 0, 8, 8)), position, 2);

	item.addComponent(std::unique_ptr<Component>(new ItemCom(ItemCom::ItemType::ROF_Up, 15, position, "Increased rate of fire")));

	return item;
}

Entity Assemblages::createPlusTenBombsItem(sf::Vector2f position)
{
	Entity item(sf::Sprite(itemsSpriteSheet, sf::IntRect(8, 0, 8, 8)), position, 2);

	item.addComponent(std::unique_ptr<Component>(new ItemCom(ItemCom::ItemType::PlusTenBombs, 5, position, "+10 bombs")));

	return item;
}