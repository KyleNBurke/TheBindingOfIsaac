#pragma once

#include "stdafx.h"
#include "Component.hpp"

class PitCollisionCom : public Component
{
public:
	PitCollisionCom();

	Component::ComponentType getType() const;
};