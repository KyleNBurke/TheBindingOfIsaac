#pragma once

#include "stdafx.h"
#include "Component.hpp"

class TurretShotCom : public Component
{
public:
	TurretShotCom();

	Component::ComponentType getType() const;

	sf::Clock timer;
	const static float shotTime;
	const static float projectileSpeed;
	bool flip;
};