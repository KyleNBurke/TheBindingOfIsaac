#include "stdafx.h"
#include "VelocityCom.hpp"

VelocityCom::VelocityCom() {}

VelocityCom::VelocityCom(sf::Vector2f velocity) : velocity(velocity)
{
	VelocityCom();
}

Component::ComponentType VelocityCom::getType() const
{
	return Component::ComponentType::Velocity;
}