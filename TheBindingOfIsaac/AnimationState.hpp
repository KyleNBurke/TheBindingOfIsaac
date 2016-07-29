#pragma once

#include "stdafx.h"

class AnimationState
{
public:
	AnimationState();

	enum AnimationStateType
	{
		Static,
		Dynamic
	};

	virtual AnimationStateType getType() const = 0;
};