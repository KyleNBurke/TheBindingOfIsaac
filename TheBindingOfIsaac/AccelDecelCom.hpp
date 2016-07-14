#pragma once

#include "stdafx.h"
#include "Component.hpp"

class AccelDecelCom : public Component
{
public:
	AccelDecelCom(float acceleration, float maxSpeed);

	Component::ComponentType getType() const;

	const float acceleration;
	const float maxSpeed;
};