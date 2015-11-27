#include "stdafx.h"
#include "PitCollisionCom.hpp"

PitCollisionCom::PitCollisionCom() {}

Component::ComponentType PitCollisionCom::getType() const
{
	return Component::ComponentType::PitCollision;
}