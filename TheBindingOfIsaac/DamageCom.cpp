#include "stdafx.h"
#include "DamageCom.hpp"

DamageCom::DamageCom(int damage) : damage(damage) {}

Component::ComponentType DamageCom::getType() const
{
	return Component::ComponentType::Damage;
}