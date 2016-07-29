#include "stdafx.h"
#include "LifetimeCom.hpp"

LifetimeCom::LifetimeCom(float lifetime) : lifetime(lifetime), elapsedTime(0.0f) {}

Component::ComponentType LifetimeCom::getType() const
{
	return Component::ComponentType::Lifetime;
}