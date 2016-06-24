#include "stdafx.h"
#include "PlayerProjectileCom.hpp"

PlayerProjectileCom::PlayerProjectileCom() : damage(1) {}

Component::ComponentType PlayerProjectileCom::getType() const
{
	return Component::ComponentType::PlayerProjectile;
}