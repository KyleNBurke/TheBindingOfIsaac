#include "stdafx.h"
#include "PlayerShotCom.hpp"

PlayerShotCom::PlayerShotCom() : fireResetTime(0.2f) {}

Component::ComponentType PlayerShotCom::getType() const
{
	return Component::ComponentType::PlayerShot;
}