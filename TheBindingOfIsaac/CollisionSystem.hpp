#pragma once

#include "stdafx.h"
#include "System.hpp"

class CollisionSystem : public System {
public:
	CollisionSystem();

	void update(std::vector<Entity>& entities);
};