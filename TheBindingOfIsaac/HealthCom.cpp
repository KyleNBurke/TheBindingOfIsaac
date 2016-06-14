#include "stdafx.h"
#include "HealthCom.hpp"

HealthCom::HealthCom(int health) : health(health) {}

Component::ComponentType HealthCom::getType() const
{
	return Component::ComponentType::Health;
}