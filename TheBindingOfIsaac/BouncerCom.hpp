#pragma once

#include "stdafx.h"
#include "Component.hpp"

class BouncerCom : public Component
{
public:
	BouncerCom();

	Component::ComponentType getType() const;
};