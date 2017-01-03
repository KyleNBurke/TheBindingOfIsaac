#include "stdafx.h"
#include "SpinShotCom.hpp"

SpinShotCom::SpinShotCom(Variation variation) :
	variation(variation),
	currentShotTime(0.0f),
	maxShotTime(variation == Regular ? 0.4f : 0.8f),
	shotAmount(6),
	shotSpeed(variation == Regular ? 300.0f : 450.0f),
	shotIndex(0)
{}

Component::ComponentType SpinShotCom::getType() const
{
	return Component::ComponentType::SpinShot;
}