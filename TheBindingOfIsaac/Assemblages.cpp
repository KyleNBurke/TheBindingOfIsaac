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
}

Entity Assemblages::createPlayer()
{
	Entity player(sf::Sprite(playerSpriteSheet, sf::IntRect(0, 0, 7, 7)));
	player.setScale((float)Utilities::getInstance().getScale(), (float)Utilities::getInstance().getScale());
	player.move(sf::Vector2f(200.0f, 200.0f));

	player.addComponent(std::unique_ptr<Component>(new PlayerControlledCom()));
	player.addComponent(std::unique_ptr<Component>(new VelocityCom(70.0f, 0.85f)));
	//add more components like collision detection

	return player;
}