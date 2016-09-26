#include "stdafx.h"
#include "PlayerControlledCom.hpp"

PlayerControlledCom::PlayerControlledCom(float maxSpeed, float acceleration) : maxSpeed(maxSpeed), acceleration(acceleration) {}

Component::ComponentType PlayerControlledCom::getType() const
{
	return Component::ComponentType::PlayerControlled;
}