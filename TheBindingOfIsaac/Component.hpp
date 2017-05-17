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
		PlayerShot,
		JimmyShot,
		SpawnerShot,
		SpinShot,
		Bouncer,
		Lifetime,
		Animation,
		PacMove,
		JimmyMove,
		FlyMove,
		DashieMove,
		WalkMove,
		Item,
		StatusEffect
	};

	Component();

	virtual ComponentType getType() const = 0;

protected:
};