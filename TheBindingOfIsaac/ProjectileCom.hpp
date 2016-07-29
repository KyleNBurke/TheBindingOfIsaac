#pragma once

#include "stdafx.h"
#include "Component.hpp"

class ProjectileCom : public Component
{
public:
	enum ProjectileType {
		Player,
		Enemy
	};

	/*enum Variation {
		Regular,
		Heatseeking,
		bounce
	}*/

	ProjectileCom(ProjectileType type);

	Component::ComponentType getType() const;

	const ProjectileType projectileType;
	bool alive;
};