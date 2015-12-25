#pragma once

#include "stdafx.h"
#include "System.hpp"
#include "VelocityCom.hpp"
#include "Utilities.hpp"

class PhysicsSystem : public System
{
public:
	PhysicsSystem();

	void update(std::vector<Entity>& entities);
};