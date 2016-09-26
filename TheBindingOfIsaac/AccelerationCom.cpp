#include "stdafx.h"
#include "AccelerationCom.hpp"

AccelerationCom::AccelerationCom() : AccelerationCom(sf::Vector2f()) {}

AccelerationCom::AccelerationCom(sf::Vector2f acceleration) :
	acceleration(acceleration) {}

Component::ComponentType AccelerationCom::getType() const
{
	return Component::ComponentType::AccelDecel;
}