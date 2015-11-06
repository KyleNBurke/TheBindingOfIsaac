#pragma once

#include "stdafx.h"
#include "System.hpp"

class RenderSystem : public System
{
public:
	RenderSystem(sf::RenderWindow& window);

	void update(std::vector<Entity>& entities);
private:
	sf::RenderWindow& window;
};