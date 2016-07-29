#pragma once

#include "stdafx.h"
#include "Component.hpp"

class LifetimeCom : public Component
{
public:
	LifetimeCom(float lifetime);

	Component::ComponentType getType() const;

	float lifetime;
	float elapsedTime;
};