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
		EnemyProjectile,
		Damage,
		Health,
		TurretShot,
		PlayerShot,
		Bouncer
	};

	Component();

	virtual ComponentType getType() const = 0;

protected:
};