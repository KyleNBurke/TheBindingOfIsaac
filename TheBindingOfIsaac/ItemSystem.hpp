#pragma once

#include "stdafx.h"
#include "System.hpp"

class ItemSystem : public System
{
public:
	ItemSystem(const sf::Time& deltaTime);
	void update(Entity& entity);

private:
	const sf::Time& deltaTime;
	bool canPickupHeart;
	bool canPickupBomb;
};