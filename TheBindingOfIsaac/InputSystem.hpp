#pragma once

#include "stdafx.h"
#include "System.hpp"
#include "Input.hpp"
#include "VelocityCom.hpp"
#include "PlayerProjectileCom.hpp"

//class GameplayState;

class InputSystem : public System
{
public:
	InputSystem();

	void update(Entity& entity);
};