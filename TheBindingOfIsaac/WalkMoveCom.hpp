#pragma once

#include "stdafx.h"
#include "Component.hpp"
#include "Utilities.hpp"

class WalkMoveCom : public Component
{
public:
	WalkMoveCom(Direction forwardDir, float speed);

	ComponentType getType() const;
	Direction setBackwardDir();

	float speed;
	bool collided;
	float elapsedTime;
	float travelTime;
	float randInterval;
	float randOffset;
	Direction forwardDir;
	Direction backwardDir;
};