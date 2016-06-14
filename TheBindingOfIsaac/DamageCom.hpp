#pragma once

#include "stdafx.h"
#include "Component.hpp"

class DamageCom : public Component
{
public:
	DamageCom(int damage);

	Component::ComponentType getType() const;

	const int damage;
};