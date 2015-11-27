#pragma once

#include "stdafx.h"
#include "Component.hpp"

class VelocityCom : public Component
{
public:
	VelocityCom(float acceleration, float deceleration);

	Component::ComponentType getType() const;

	sf::Vector2f& getVelocity();
	sf::Vector2i& getDirection();
	float getAcceleration() const;
	float getDeceleration() const;

private:
	sf::Vector2f velocity;
	sf::Vector2i direction;
	const float acceleration;
	const float deceleration;
};