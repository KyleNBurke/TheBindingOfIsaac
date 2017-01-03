#include "stdafx.h"
#include "AccelerationCom.hpp"

AccelerationCom::AccelerationCom() : AccelerationCom(1.0f) {}

AccelerationCom::AccelerationCom(float drag) : drag(drag) {}


Component::ComponentType AccelerationCom::getType() const
{
	return Component::ComponentType::AccelDecel;
}