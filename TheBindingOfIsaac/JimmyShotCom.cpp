#include "stdafx.h"
#include "JimmyShotCom.hpp"

JimmyShotCom::JimmyShotCom(Variation variation) :
	variation(variation),
	currentShotTime(0.0f),
	randShotTimeAmount(1.0f),
	maxShotTime((float)std::rand() / (float)RAND_MAX * randShotTimeAmount + 1.0f),
	projectileSpeed(variation == Direct ? 500.0f : 250.0f) {}

Component::ComponentType JimmyShotCom::getType() const
{
	return Component::ComponentType::JimmyShot;
}