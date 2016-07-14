#include "stdafx.h"
#include "Assemblages.hpp"

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
}

Entity Assemblages::createPlayer(sf::Vector2f position)
{
	Entity player(sf::Sprite(playerSpriteSheet, sf::IntRect(0, 0, 7, 6)), sf::IntRect(1, 1, 5, 4));
	player.sprite.setScale((float)Utilities::getInstance().getScale(), (float)Utilities::getInstance().getScale());
	player.sprite.setPosition(position);

	player.addComponent(std::unique_ptr<Component>(new PlayerControlledCom()));
	player.addComponent(std::unique_ptr<Component>(new VelocityCom()));
	player.addComponent(std::unique_ptr<Component>(new AccelDecelCom(0.1f, 500.0f)));
	player.addComponent(std::unique_ptr<Component>(new PitCollisionCom()));
	player.addComponent(std::unique_ptr<Component>(new WallCollisionCom()));
	player.addComponent(std::unique_ptr<Component>(new HealthCom(10)));
	player.addComponent(std::unique_ptr<Component>(new PlayerShotCom()));

	return player;
}

Entity Assemblages::createPlayerProjectile(sf::Vector2f position, sf::Vector2f velocity)
{
	Entity projectile(sf::Sprite(projectilesSpriteSheet, sf::IntRect(0, 0, 4, 4)), sf::IntRect(1, 1, 2, 2));
	projectile.sprite.setScale((float)Utilities::getInstance().getScale(), (float)Utilities::getInstance().getScale());
	projectile.sprite.setPosition(sf::Vector2f(position.x + 1.5f * (float)Utilities::getInstance().getScale(), position.y + 1.5f * (float)Utilities::getInstance().getScale()));
	projectile.addComponent(std::unique_ptr<Component>(new VelocityCom(velocity)));
	projectile.addComponent(std::unique_ptr<Component>(new PlayerProjectileCom()));

	return projectile;
}

Entity Assemblages::createRegularProjectile(sf::Vector2f position, sf::Vector2f velocity)
{
	Entity projectile(sf::Sprite(projectilesSpriteSheet, sf::IntRect(4, 0, 4, 4)), sf::IntRect(1, 1, 2, 2));
	projectile.sprite.setScale((float)Utilities::getInstance().getScale(), (float)Utilities::getInstance().getScale());
	projectile.sprite.setPosition(position);
	projectile.addComponent(std::unique_ptr<Component>(new VelocityCom(velocity)));
	projectile.addComponent(std::unique_ptr<Component>(new EnemyProjectileCom(EnemyProjectileCom::Type::Regular)));

	return projectile;
}

Entity Assemblages::createTurret(sf::Vector2f position)
{
	Entity turret(sf::Sprite(enemySpriteSheet, sf::IntRect(0, 0, 6, 6)));
	turret.sprite.setScale((float)Utilities::getInstance().getScale(), (float)Utilities::getInstance().getScale());
	turret.sprite.setPosition(position);
	turret.addComponent(std::unique_ptr<Component>(new HealthCom(3)));
	turret.addComponent(std::unique_ptr<Component>(new TurretShotCom()));

	return turret;
}

Entity Assemblages::createBouncer(sf::Vector2f position, sf::Vector2f direction)
{
	Entity bouncer(sf::Sprite(enemySpriteSheet, sf::IntRect(6, 0, 10, 10)));
	bouncer.sprite.setScale((float)Utilities::getInstance().getScale(), (float)Utilities::getInstance().getScale());
	bouncer.sprite.setPosition(position);
	bouncer.addComponent(std::unique_ptr<Component>(new VelocityCom(direction * 50.0f)));
	bouncer.addComponent(std::unique_ptr<Component>(new BouncerCom()));
	bouncer.addComponent(std::unique_ptr<Component>(new HealthCom(3)));

	return bouncer;
}