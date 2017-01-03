#pragma once

#include "stdafx.h"
#include "Component.hpp"

class FlyMoveCom : public Component
{
public:
	enum Variation {
		Attack,
		Bomb,
		Daddy
	};

	FlyMoveCom(Variation variation);

	ComponentType getType() const;

	const Variation variation;
	const float speed;

private:
	float setSpeed(Variation variation);
};