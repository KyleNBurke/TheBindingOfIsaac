#pragma once

#include "stdafx.h"
#include "Component.hpp"

class SpinShotCom : public Component
{
public:
	enum Variation {
		Regular,
		Bomb
	};

	SpinShotCom(Variation variation);

	Component::ComponentType getType() const;

	const Variation variation;
	float currentShotTime;
	const float maxShotTime;
	const int shotAmount;
	const float shotSpeed;
	int shotIndex;
};