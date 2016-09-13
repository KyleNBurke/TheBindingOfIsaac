#include "stdafx.h"
#include "BouncerCom.hpp"

BouncerCom::BouncerCom() : projectileSpeed(300.0f) {}

Component::ComponentType BouncerCom::getType() const
{
	return Component::ComponentType::Bouncer;
}