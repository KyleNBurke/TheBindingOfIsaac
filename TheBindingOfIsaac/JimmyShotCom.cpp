#include "stdafx.h"
#include "JimmyShotCom.hpp"

JimmyShotCom::JimmyShotCom() : currentShotTime(0.0f), maxShotTime(1.5f), projectileSpeed(500.0f) {}

Component::ComponentType JimmyShotCom::getType() const
{
	return Component::ComponentType::JimmyShot;
}