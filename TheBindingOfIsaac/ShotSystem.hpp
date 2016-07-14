#pragma once

#include "stdafx.h"
#include "System.hpp"

class ShotSystem : public System
{
public:
	ShotSystem(const sf::Time& deltaTime);

	void update(Entity& entity);

private:
	const sf::Time& deltaTime;
};