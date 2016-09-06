#pragma once

#include "stdafx.h"
#include "System.hpp"

class FlashSystem : public System
{
public:
	FlashSystem(const sf::Time& deltaTime);

	void update(Entity& entity);

private:
	const sf::Time& deltaTime;
	bool flip;
	const int maxPlayerFlashes;
	int currPlayerFlashes;
};