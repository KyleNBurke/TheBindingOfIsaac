#pragma once

#include "stdafx.h"
#include "System.hpp"
#include "VelocityCom.hpp"
#include "Utilities.hpp"
#include "Map.hpp"

class CollisionSystem : public System {
public:
	CollisionSystem(const sf::Time& deltaTime);

	void update(std::vector<Entity>& entities);

private:
	enum Direction { Horizontal, Vertical };

	void resolveCollisions(Direction direction, Entity& entity, sf::Vector2f& position, sf::Vector2f& velocity, bool hasPitCollision, bool hasWallCollision);

	const sf::Time& deltaTime;
};