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

	enum ProjectileVariation {
		Regular,
		Bomb
	};

	ProjectileCom(ProjectileType type, ProjectileVariation variation);

	Component::ComponentType getType() const;

	const ProjectileType projectileType;
	const ProjectileVariation projectileVariation;
	bool alive;
};