#pragma once

#include "stdafx.h"

class Component
{
public:
	enum ComponentType {
		PlayerControlled,
		Velocity,
		PitCollision,
		WallCollision,
		PlayerProjectileCom
	};

	Component();

	virtual ComponentType getType() const = 0;

protected:
};