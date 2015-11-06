#include "stdafx.h"
#include "VelocityCom.hpp"

VelocityCom::VelocityCom(float acceleration, float deceleration) : acceleration(acceleration), deceleration(deceleration) {}

Component::ComponentType VelocityCom::getType() const
{
	return Component::ComponentType::Velocity;
}