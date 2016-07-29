#pragma once

#include "stdafx.h"
#include "AnimationState.hpp"

class AnimationStateStatic : public AnimationState
{
public:
	AnimationStateStatic(sf::IntRect frame);

	AnimationState::AnimationStateType getType() const;

	sf::IntRect frame;
	bool set;
};