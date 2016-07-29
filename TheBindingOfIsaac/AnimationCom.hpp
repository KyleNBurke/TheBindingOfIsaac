#pragma once

#include "stdafx.h"
#include "Component.hpp"
#include "AnimationState.hpp"

class AnimationCom : public Component
{
public:
	AnimationCom();

	Component::ComponentType getType() const;

	std::vector<std::shared_ptr<AnimationState>> states;
	int currentState;
};