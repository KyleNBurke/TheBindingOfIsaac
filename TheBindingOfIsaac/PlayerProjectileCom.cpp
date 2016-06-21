#include "stdafx.h"
#include "PlayerProjectileCom.hpp"

PlayerProjectileCom::PlayerProjectileCom() {}

Component::ComponentType PlayerProjectileCom::getType() const
{
	return Component::ComponentType::PlayerProjectile;
}