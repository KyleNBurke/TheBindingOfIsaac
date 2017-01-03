#pragma once

#include "stdafx.h"
#include "Component.hpp"

class AccelerationCom : public Component
{
public:
	AccelerationCom();
	AccelerationCom(float drag);

	Component::ComponentType getType() const;

	sf::Vector2f acceleration;
	const float drag;
};