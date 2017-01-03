#pragma once

#include "stdafx.h"
#include "Component.hpp"

class SpawnerShotCom : public Component
{
public:
	enum Variation {
		Attack,
		Bomb,
		Daddy
	};

	SpawnerShotCom(Variation variation);

	Component::ComponentType getType() const;

	const Variation variation;
	float currentShotTime;
	const float randShotTimeAmount;
	float maxShotTime;
};