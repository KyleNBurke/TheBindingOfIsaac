#pragma once

#include "stdafx.h"
#include "System.hpp"

class ShotSystem : public System
{
public:
	ShotSystem();

	void update(Entity& entity);
};