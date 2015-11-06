#include "stdafx.h"
#include "PlayerControlledCom.hpp"

PlayerControlledCom::PlayerControlledCom() {}

Component::ComponentType PlayerControlledCom::getType() const
{
	return Component::ComponentType::PlayerControlled;
}