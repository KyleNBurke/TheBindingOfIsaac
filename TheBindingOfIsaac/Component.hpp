#pragma once

#include "stdafx.h"

class Component
{
public:
	enum ComponentType {
		PlayerControlled,
		Velocity
	};

	Component();

	virtual ComponentType getType() const = 0;

protected:
};