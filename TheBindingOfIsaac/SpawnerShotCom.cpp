#include "stdafx.h"
#include "SpawnerShotCom.hpp"

SpawnerShotCom::SpawnerShotCom(Variation variation) :
	variation(variation),
	currentShotTime(0.0f),
	randShotTimeAmount(1.0f),
	maxShotTime((float)std::rand() / (float)RAND_MAX * randShotTimeAmount + 2.0f) {}

Component::ComponentType SpawnerShotCom::getType() const
{
	return Component::ComponentType::SpawnerShot;
}