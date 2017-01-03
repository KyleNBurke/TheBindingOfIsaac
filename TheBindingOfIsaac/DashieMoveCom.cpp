#include "stdafx.h"
#include "DashieMoveCom.hpp"

DashieMoveCom::DashieMoveCom(Variation variation) :
	variation(variation),
	currentMoveTime(0.0f),
	baseMoveTimeAmount(1.5f),
	randomMoveTimeAmount(1.5f),
	maxMoveTime((float)std::rand() / RAND_MAX * randomMoveTimeAmount + baseMoveTimeAmount),
	prevDirectionRad((float)std::rand() / RAND_MAX * 2 * 3.1415f),
	speed(350.0f),
	decel(4.0f)
	{}

Component::ComponentType DashieMoveCom::getType() const
{
	return Component::ComponentType::DashieMove;
}