#pragma once

#include "stdafx.h"
#include "Component.hpp"

class HealthCom : public Component
{
public:
	HealthCom(int health);

	Component::ComponentType getType() const;

	int health;
};