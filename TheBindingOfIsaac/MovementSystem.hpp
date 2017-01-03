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
	void calculatePacTurn(Entity& entity);
	void calculateWalkTurn(Entity& entity);
	bool evaluateDirection(Entity& entity, Direction d, Direction forwardDir);
	bool evaluateWalkDirection(Direction d, int left, int right, int top, int bottom);
};