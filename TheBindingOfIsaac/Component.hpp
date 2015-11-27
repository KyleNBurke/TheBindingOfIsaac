#pragma once

#include "stdafx.h"

class Component
{
public:
	enum ComponentType {
		PlayerControlled,
		Velocity,
		PitCollision,
		WallCollision
	};

	Component();

	virtual ComponentType getType() const = 0;

protected:
};