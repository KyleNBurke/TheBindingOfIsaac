#pragma once

#include "stdafx.h"
#include "Component.hpp"

class PlayerShotCom : public Component
{
public:
	PlayerShotCom();

	Component::ComponentType getType() const;

	sf::Clock fireResetClock;
	const float fireResetTime;
};
