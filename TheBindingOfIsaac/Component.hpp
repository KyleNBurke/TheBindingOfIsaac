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
		Damage,
		Health,
		TurretShot,
		PlayerShot,
		Bouncer,
		Lifetime,
		Animation
	};

	Component();

	virtual ComponentType getType() const = 0;

protected:
};