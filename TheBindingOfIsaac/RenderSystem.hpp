#pragma once

#include "stdafx.h"
#include "System.hpp"

class RenderSystem : public System
{
public:
	RenderSystem(sf::RenderWindow& window);

	void update(Entity& entity);
private:
	sf::RenderWindow& window;
};