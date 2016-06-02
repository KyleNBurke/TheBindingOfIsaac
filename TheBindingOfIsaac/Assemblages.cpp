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
}

Entity Assemblages::createPlayer()
{
	Entity player(sf::Sprite(playerSpriteSheet, sf::IntRect(0, 0, 7, 7)));
	player.setScale((float)Utilities::getInstance().getScale(), (float)Utilities::getInstance().getScale());
	player.move(sf::Vector2f(200.0f, 200.0f));

	player.addComponent(std::unique_ptr<Component>(new PlayerControlledCom()));
	player.addComponent(std::unique_ptr<Component>(new VelocityCom(70.0f, 0.85f)));
	player.addComponent(std::unique_ptr<Component>(new PitCollisionCom()));
	player.addComponent(std::unique_ptr<Component>(new WallCollisionCom()));

	return player;
}

Entity Assemblages::createProjectile(sf::Vector2f position, sf::Vector2f velocity)
{
	Entity projectile(sf::Sprite(projectilesSpriteSheet, sf::IntRect(0, 0, 4, 4)));
	projectile.setScale((float)Utilities::getInstance().getScale(), (float)Utilities::getInstance().getScale());
	projectile.getPosition() = position;
	projectile.getSprite().setPosition(position);
	projectile.addComponent(std::unique_ptr<Component>(new VelocityCom(velocity)));

	return projectile;
}