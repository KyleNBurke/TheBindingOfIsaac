#pragma once

#include "stdafx.h"
#include "Component.hpp"

class PlayerControlledCom : public Component
{
public:
	PlayerControlledCom();

	Component::ComponentType getType() const;
};