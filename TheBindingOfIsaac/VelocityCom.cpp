#include "stdafx.h"
#include "VelocityCom.hpp"

VelocityCom::VelocityCom() : acceleration(0.0f), deceleration(0.0f) {}

VelocityCom::VelocityCom(float acceleration, float deceleration) : acceleration(acceleration), deceleration(deceleration) {}

VelocityCom::VelocityCom(sf::Vector2f velocity) : velocity(velocity), acceleration(0.0f), deceleration(0.0f)
{
	VelocityCom();
}

Component::ComponentType VelocityCom::getType() const
{
	return Component::ComponentType::Velocity;
}

sf::Vector2f& VelocityCom::getVelocity()
{
	return velocity;
}

sf::Vector2f& VelocityCom::getDirection()
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