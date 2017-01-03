#pragma once

#include "stdafx.h"
#include "Component.hpp"

class DashieMoveCom : public Component
{
public:
	enum Variation {
		Random,
		Direct
	};

	DashieMoveCom(Variation variation);

	ComponentType getType() const;

	const Variation variation;
	float currentMoveTime;
	float maxMoveTime;
	const float baseMoveTimeAmount;
	const float randomMoveTimeAmount;
	float prevDirectionRad;
	const float speed;
	const float decel;
};