#pragma once

#include "stdafx.h"
#include "System.hpp"

class AnimationSystem : public System
{
public:
	AnimationSystem(const sf::Time& deltaTime);

	void update(Entity& entity);

private:
	const sf::Time& deltaTime;
};