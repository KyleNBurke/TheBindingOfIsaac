#include "stdafx.h"
#include "HealthCom.hpp"

const float HealthCom::maxFlashTime = 0.08f;

HealthCom::HealthCom(int health) : health(health), flashing(false), currFlashTime(0.0f) {}

Component::ComponentType HealthCom::getType() const
{
	return Component::ComponentType::Health;
}