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
		JimmyShot,
		Bouncer,
		Lifetime,
		Animation,
		PacMove,
		JimmyMove,
		Item
	};

	Component();

	virtual ComponentType getType() const = 0;

protected:
};