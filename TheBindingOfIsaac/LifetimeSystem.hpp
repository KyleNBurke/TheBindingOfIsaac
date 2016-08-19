#pragma once

#include "stdafx.h"
#include "System.hpp"

class LifetimeSystem : public System
{
public:
	LifetimeSystem(const sf::Time& deltaTime);

	void update(Entity& entity);

private:
	const sf::Time& deltaTime;
};