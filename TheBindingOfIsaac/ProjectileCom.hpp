#pragma once

#include "stdafx.h"
#include "Component.hpp"

class ProjectileCom : public Component
{
public:
	enum ProjectileType {
		Player,
		Regular
	};

	ProjectileCom(ProjectileType projectileType);

	Component::ComponentType getType() const;

	ProjectileType projectileType;
};