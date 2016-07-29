#pragma once

#include "stdafx.h"
#include "System.hpp"
#include "Input.hpp"

class InputSystem : public System
{
public:
	InputSystem();

	void update(Entity& entity);
};