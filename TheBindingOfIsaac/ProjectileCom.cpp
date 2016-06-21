#include "stdafx.h"
#include "ProjectileCom.hpp"

ProjectileCom::ProjectileCom(ProjectileType projectileType) : projectileType(projectileType) {}

Component::ComponentType ProjectileCom::getType() const
{
	return Component::ComponentType::Projectile;
}