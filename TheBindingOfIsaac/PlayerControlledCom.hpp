#pragma once

#include "stdafx.h"
#include "Component.hpp"

class PlayerControlledCom : public Component
{
public:
	PlayerControlledCom(float maxSpeed, float acceleration);

	Component::ComponentType getType() const;

	const float maxSpeed;
	const float acceleration;
};