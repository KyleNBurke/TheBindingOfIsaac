#pragma once

#include "stdafx.h"
#include "System.hpp"
#include "VelocityCom.hpp"
#include "AccelDecelCom.hpp"
#include "Utilities.hpp"
#include "Floor.hpp"
#include "HUD.hpp"

class PhysicsSystem : public System
{
public:
	PhysicsSystem(const sf::Time& deltaTime);

	void update(Entity& entity);

private:
	enum Direction { Horizontal, Vertical };

	void resolveCollisions(Direction direction, Entity& entity, bool hasPitCollision, bool hasWallCollision);

	const sf::Time& deltaTime;
};