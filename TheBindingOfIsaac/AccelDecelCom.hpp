#pragma once

#include "stdafx.h"
#include "Component.hpp"

class AccelDecelCom : public Component
{
public:
	AccelDecelCom();
	AccelDecelCom(float acceleration, float deceleration);

	Component::ComponentType getType() const;

	const float acceleration;
	const float deceleration;
};