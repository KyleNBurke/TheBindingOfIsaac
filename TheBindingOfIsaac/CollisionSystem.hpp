#pragma once

#include "stdafx.h"
#include "System.hpp"
#include "VelocityCom.hpp"
#include "Utilities.hpp"
#include "Map.hpp"

class CollisionSystem : public System {
public:
	CollisionSystem();

	void update(std::vector<Entity>& entities);

private:
	enum Direction { Horizontal, Vertical };

	void resolveCollisions(Direction direction, Entity& entity, VelocityCom& velocityCom, bool hasPitCollision, bool hasWallCollision);
};