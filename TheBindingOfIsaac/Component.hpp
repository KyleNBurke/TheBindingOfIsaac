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
		Projectile,
		Health,
		TurretShot,
		PlayerShot,
		Bouncer,
		Lifetime,
		Animation,
		PacMove
	};

	Component();

	virtual ComponentType getType() const = 0;

protected:
};