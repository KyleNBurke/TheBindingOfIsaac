#include "stdafx.h"
#include "VelocityCom.hpp"

VelocityCom::VelocityCom(float acceleration, float deceleration) : acceleration(acceleration), deceleration(deceleration) {}

Component::ComponentType VelocityCom::getType() const
{
	return Component::ComponentType::Velocity;
}

sf::Vector2f& VelocityCom::getVelocity()
{
	return velocity;
}

sf::Vector2i& VelocityCom::getDirection()
{
	return direction;
}

float VelocityCom::getAcceleration() const
{
	return acceleration;
}

float VelocityCom::getDeceleration() const
{
	return deceleration;
}