#pragma once

#include "stdafx.h"

class Player
{
public:
	Player();

	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

private:
	enum Direction { horizontal, vertical };

	void resolveCollisions(Direction direction);
	sf::FloatRect getPlayerBounds() const;

	sf::Texture spriteSheet;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Vector2f velocity;
	const float acceleration;
	const float deceleration;
};