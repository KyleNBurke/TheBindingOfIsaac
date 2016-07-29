#include "stdafx.h"
#include "AnimationStateDynamic.hpp"

AnimationStateDynamic::AnimationStateDynamic(sf::IntRect initialFrame, int offsetX, int offsetY, int frameCount, float frameTime) :
	offsetX(offsetX), offsetY(offsetY), initialFrame(initialFrame), frameCount(frameCount), frameTime(frameTime), elapsedTime(0.0f), currentFrame(0) {}

AnimationState::AnimationStateType AnimationStateDynamic::getType() const
{
	return AnimationState::AnimationStateType::Dynamic;
}