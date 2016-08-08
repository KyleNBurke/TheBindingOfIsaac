#pragma once

#include "System.hpp"
#include "Utilities.hpp"

class MovementSystem : public System
{
public:
	MovementSystem(const sf::Time& deltaTime);

	void update(Entity& entity);

	sf::RectangleShape rect;

private:
	const sf::Time& deltaTime;

	bool searchForPlayer(Entity& entity);
	void calculateTurn(Entity& entity);
	bool evaluateDirection(Entity& entity, Direction d, Direction forwardDir);
};