#include "stdafx.h"
#include "AnimationCom.hpp"

AnimationCom::AnimationCom() : currentState(0) {}

Component::ComponentType AnimationCom::getType() const
{
	return Component::ComponentType::Animation;
}