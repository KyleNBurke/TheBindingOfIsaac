#include "stdafx.h"
#include "PlayerProjectileCom.hpp"
#include "Assemblages.hpp"

const float PlayerProjectileCom::velocityConst = 800.0f;
const float PlayerProjectileCom::fireResetTime = 0.375;
sf::Clock PlayerProjectileCom::fireResetClock = sf::Clock();

PlayerProjectileCom::PlayerProjectileCom() {}

Component::ComponentType PlayerProjectileCom::getType() const
{
	return Component::ComponentType::PlayerProjectileCom;
}