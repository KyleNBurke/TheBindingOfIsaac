#pragma once

#include "stdafx.h"
#include "AnimationState.hpp"

class AnimationStateDynamic : public AnimationState
{
public:
	AnimationStateDynamic(sf::IntRect initialFrame, int frameCount, float frameTime);

	AnimationState::AnimationStateType getType() const;

	const sf::IntRect initialFrame;
	const int frameCount;
	float frameTime;
	float elapsedTime;
	int currentFrame;
};
