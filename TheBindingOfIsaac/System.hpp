#pragma once

#include "stdafx.h"
#include "Entity.hpp"

class System
{
public:
	System();

	virtual void update(Entity& entity) = 0;
};