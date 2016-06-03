#pragma once

#include "stdafx.h"
#include "Component.hpp"

class VelocityCom : public Component
{
public:
	VelocityCom();
	VelocityCom(sf::Vector2f velocity);

	Component::ComponentType getType() const;

	sf::Vector2f velocity;
	sf::Vector2f direction;
};