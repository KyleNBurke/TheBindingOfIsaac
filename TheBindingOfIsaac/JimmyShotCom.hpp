#pragma once

#include "stdafx.h"
#include "Component.hpp"

class JimmyShotCom : public Component
{
public:
	JimmyShotCom();

	Component::ComponentType getType() const;

	float currentShotTime;
	const float randShotTimeAmount;
	float maxShotTime;
	const float projectileSpeed;
};