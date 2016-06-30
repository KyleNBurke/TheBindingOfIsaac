#include "stdafx.h"
#include "BouncerCom.hpp"

BouncerCom::BouncerCom() {}

Component::ComponentType BouncerCom::getType() const
{
	return Component::ComponentType::Bouncer;
}