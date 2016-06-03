#include "stdafx.h"
#include "AccelDecelCom.hpp"

AccelDecelCom::AccelDecelCom() : acceleration(0), deceleration(0) {}

AccelDecelCom::AccelDecelCom(float acceleration, float deceleration) : acceleration(acceleration), deceleration(deceleration) {}

Component::ComponentType AccelDecelCom::getType() const
{
	return Component::ComponentType::AccelDecel;
}