#include "stdafx.h"
#include "ProjectileCom.hpp"

ProjectileCom::ProjectileCom(ProjectileType projectileType, ProjectileVariation variation) :
	projectileType(projectileType), projectileVariation(variation), alive(true) {}

Component::ComponentType ProjectileCom::getType() const
{
	return Component::ComponentType::Projectile;
}