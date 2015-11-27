#include "stdafx.h"
#include "WallCollisionCom.hpp"

WallCollisionCom::WallCollisionCom() {}

Component::ComponentType WallCollisionCom::getType() const
{
	return Component::ComponentType::WallCollision;
}