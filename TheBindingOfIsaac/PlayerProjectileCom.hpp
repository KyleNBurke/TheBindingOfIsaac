#pragma once

#include "stdafx.h"
#include "Component.hpp"

class PlayerProjectileCom : public Component
{
public:
	PlayerProjectileCom();

	Component::ComponentType getType() const;
};