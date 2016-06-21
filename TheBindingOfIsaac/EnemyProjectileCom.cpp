#include "stdafx.h"
#include "EnemyProjectileCom.hpp"

EnemyProjectileCom::EnemyProjectileCom(Type type) : type(type) {}

Component::ComponentType EnemyProjectileCom::getType() const
{
	return Component::ComponentType::EnemyProjectile;
}