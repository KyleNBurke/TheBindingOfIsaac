#pragma once

#include "stdafx.h"
#include "Component.hpp"

class VelocityCom : public Component
{
public:
	VelocityCom();
	VelocityCom(float acceleration, float deceleration);
	VelocityCom(sf::Vector2f velocity);

	Component::ComponentType getType() const;

	sf::Vector2f& getVelocity();
	sf::Vector2f& getDirection();
	float getAcceleration() const;
	float getDeceleration() const;

private:
	sf::Vector2f velocity;
	sf::Vector2f direction;
	const float acceleration;
	const float deceleration;
};