#pragma once

#include "stdafx.h"
#include "System.hpp"
#include "VelocityCom.hpp"
#include "AccelDecelCom.hpp"
#include "Utilities.hpp"
#include "Map.hpp"
#include "Room.hpp"

class PhysicsSystem : public System
{
public:
	PhysicsSystem(const sf::Time& deltaTime);

	void update(std::vector<Entity>& entities);

private:
	enum Direction { Horizontal, Vertical };

	void resolveCollisions(Direction direction, Entity& entity, bool hasPitCollision, bool hasWallCollision);
	sf::FloatRect getEntityBounds(const Entity& entity);

	const sf::Time& deltaTime;
};