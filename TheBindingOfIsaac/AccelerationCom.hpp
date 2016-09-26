#pragma once

#include "stdafx.h"
#include "Component.hpp"

class AccelerationCom : public Component
{
public:
	AccelerationCom();
	AccelerationCom(sf::Vector2f acceleration);

	Component::ComponentType getType() const;

	//const float acceleration;
	sf::Vector2f acceleration;
	//const float maxSpeed;
};