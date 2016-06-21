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
	playerSpriteSheet.loadFromFile("Player.png");
	projectilesSpriteSheet.loadFromFile("Projectiles.png");
	enemySpriteSheet.loadFromFile("Enemies.png");
}

Entity Assemblages::createPlayer()
{
	Entity player(sf::Sprite(playerSpriteSheet, sf::IntRect(0, 0, 7, 7)));
	player.sprite.setScale((float)Utilities::getInstance().getScale(), (float)Utilities::getInstance().getScale());
	player.position += sf::Vector2f(200.0f, 200.0f);

	player.addComponent(std::unique_ptr<Component>(new PlayerControlledCom()));
	player.addComponent(std::unique_ptr<Component>(new VelocityCom()));
	player.addComponent(std::unique_ptr<Component>(new AccelDecelCom(70.0f, 0.85f)));
	player.addComponent(std::unique_ptr<Component>(new PitCollisionCom()));
	player.addComponent(std::unique_ptr<Component>(new WallCollisionCom()));

	return player;
}

Entity Assemblages::createPlayerProjectile(sf::Vector2f position, sf::Vector2f velocity)
{
	Entity projectile(sf::Sprite(projectilesSpriteSheet, sf::IntRect(0, 0, 4, 4)));
	projectile.sprite.setScale((float)Utilities::getInstance().getScale(), (float)Utilities::getInstance().getScale());
	projectile.position.x = position.x + 1.5f * (float)Utilities::getInstance().getScale();
	projectile.position.y = position.y + 1.5f * (float)Utilities::getInstance().getScale();
	projectile.addComponent(std::unique_ptr<Component>(new VelocityCom(velocity)));
	projectile.addComponent(std::unique_ptr<Component>(new ProjectileCom(ProjectileCom::ProjectileType::Player)));

	return projectile;
}

Entity Assemblages::createRegularProjectile(sf::Vector2f position, sf::Vector2f velocity)
{
	Entity projectile(sf::Sprite(projectilesSpriteSheet, sf::IntRect(4, 0, 4, 4)));
	projectile.sprite.setScale((float)Utilities::getInstance().getScale(), (float)Utilities::getInstance().getScale());
	projectile.position = position;
	projectile.addComponent(std::unique_ptr<Component>(new VelocityCom(velocity)));
	projectile.addComponent(std::unique_ptr<Component>(new ProjectileCom(ProjectileCom::ProjectileType::Regular)));

	return projectile;
}

Entity Assemblages::createTurret(sf::Vector2f position)
{
	Entity turret(sf::Sprite(enemySpriteSheet, sf::IntRect(0, 0, 6, 6)));
	turret.sprite.setScale((float)Utilities::getInstance().getScale(), (float)Utilities::getInstance().getScale());
	turret.sprite.setPosition(position);
	turret.addComponent(std::unique_ptr<Component>(new DamageCom(1)));
	turret.addComponent(std::unique_ptr<Component>(new HealthCom(3)));
	turret.addComponent(std::unique_ptr<Component>(new TurretShotCom()));

	return turret;
}