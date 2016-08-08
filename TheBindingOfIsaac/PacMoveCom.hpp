#pragma once

#include "stdafx.h"
#include "Component.hpp"
#include "Utilities.hpp"

class PacMoveCom : public Component
{
public:
	PacMoveCom(Direction forwardsDir);

	ComponentType getType() const;

	enum State { Passive, Aggressive, Rotating };
	State state;
	Direction forwardsDir;
	Direction backwardsDir;
	static const float passiveSpeed;
	static const float aggressiveSpeed;
	bool collided;
	float elapsedTime;
	float travelTime;
	static const float randInterval;
	static const float randOffset;
};