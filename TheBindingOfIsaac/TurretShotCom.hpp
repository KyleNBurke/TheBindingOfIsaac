#pragma once

#include "stdafx.h"
#include "Component.hpp"

class TurretShotCom : public Component
{
public:
	TurretShotCom();

	ComponentType getType() const;

	float elapsedTime;
	const static float shotTime;
	const static float projectileSpeed;
	bool flip;
};