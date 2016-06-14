#pragma once

#include "stdafx.h"

class Component
{
public:
	enum ComponentType {
		PlayerControlled,
		Velocity,
		AccelDecel,
		PitCollision,
		WallCollision,
		PlayerProjectile,
		Damage,
		Health
	};

	Component();

	virtual ComponentType getType() const = 0;

protected:
};