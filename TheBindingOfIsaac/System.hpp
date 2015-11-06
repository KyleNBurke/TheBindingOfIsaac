#pragma once

#include "stdafx.h"
#include "Entity.hpp"

class System
{
public:
	System();

	virtual void update(std::vector<Entity>& entities) = 0;
};