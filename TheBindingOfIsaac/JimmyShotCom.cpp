#include "stdafx.h"
#include "JimmyShotCom.hpp"

JimmyShotCom::JimmyShotCom() :
	currentShotTime(0.0f),
	randShotTimeAmount(1.0f),
	maxShotTime((float)std::rand() / (float)RAND_MAX * randShotTimeAmount + 1.0f),
	projectileSpeed(500.0f) {}

Component::ComponentType JimmyShotCom::getType() const
{
	return Component::ComponentType::JimmyShot;
}