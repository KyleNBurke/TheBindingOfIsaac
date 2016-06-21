#include "stdafx.h"
#include "PlayerControlledCom.hpp"

PlayerControlledCom::PlayerControlledCom() : fireResetTime(0.1f) {}

Component::ComponentType PlayerControlledCom::getType() const
{
	return Component::ComponentType::PlayerControlled;
}