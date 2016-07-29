#include "stdafx.h"
#include "AnimationStateStatic.hpp"

AnimationStateStatic::AnimationStateStatic(sf::IntRect frame) : frame(frame), set(false) {}

AnimationState::AnimationStateType AnimationStateStatic::getType() const
{
	return AnimationState::AnimationStateType::Static;
}