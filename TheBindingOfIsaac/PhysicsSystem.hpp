#pragma once

#include "stdafx.h"
#include "System.hpp"
#include "VelocityCom.hpp"

class PhysicsSystem : public System
{
public:
	PhysicsSystem(const sf::Time& deltaTime);

	void update(std::vector<Entity>& entities);

private:
	const sf::Time& deltaTime;
};