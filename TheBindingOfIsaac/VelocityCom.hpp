#pragma once

#include "stdafx.h"
#include "Component.hpp"

class VelocityCom : public Component
{
public:
	VelocityCom(float acceleration, float deceleration);

	Component::ComponentType getType() const;

	sf::Vector2f velocity;
	sf::Vector2i direction;
	const float acceleration;
	const float deceleration;
};