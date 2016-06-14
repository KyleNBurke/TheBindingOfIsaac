#include "stdafx.h"
#include "PlayerProjectileCom.hpp"
#include "Assemblages.hpp"

const float PlayerProjectileCom::velocityConst = 600.0f;
const float PlayerProjectileCom::fireResetTime = 0.1f;//0.375f;
sf::Clock PlayerProjectileCom::fireResetClock = sf::Clock();

PlayerProjectileCom::PlayerProjectileCom() {}

Component::ComponentType PlayerProjectileCom::getType() const
{
	return Component::ComponentType::PlayerProjectile;
}