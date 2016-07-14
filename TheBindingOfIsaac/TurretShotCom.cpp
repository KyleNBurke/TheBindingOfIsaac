#include "stdafx.h"
#include "TurretShotCom.hpp"

const float TurretShotCom::shotTime = 0.8f;
const float TurretShotCom::projectileSpeed = 200.0f;

TurretShotCom::TurretShotCom() : elapsedTime(0.0f), flip(true) {}

Component::ComponentType TurretShotCom::getType() const
{
	return Component::ComponentType::TurretShot;
}