#include "stdafx.h"
#include "FlyMoveCom.hpp"

FlyMoveCom::FlyMoveCom(Variation variation) : variation(variation), speed(setSpeed(variation)) {}

Component::ComponentType FlyMoveCom::getType() const
{
	return Component::ComponentType::FlyMove;
}

float FlyMoveCom::setSpeed(FlyMoveCom::Variation variation)
{
	switch(variation)
	{
		case Variation::Attack:
			return 150.0f;
		case Variation::Bomb:
			return 150.0f;
		case Variation::Daddy:
			return 200.0f;
		default:
			return 200.0f;
	}
}