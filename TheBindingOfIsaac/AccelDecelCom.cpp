#include "stdafx.h"
#include "AccelDecelCom.hpp"

AccelDecelCom::AccelDecelCom(float acceleration, float maxSpeed) :
	acceleration(acceleration), maxSpeed(maxSpeed) {}

Component::ComponentType AccelDecelCom::getType() const
{
	return Component::ComponentType::AccelDecel;
}