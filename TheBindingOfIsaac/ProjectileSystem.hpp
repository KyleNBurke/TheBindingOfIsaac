#pragma once

#include "System.hpp"
#include "PlayerProjectileCom.hpp"

class ProjectileSystem : public System
{
public:
	ProjectileSystem();

	void update(std::vector<Entity>& entities);
};