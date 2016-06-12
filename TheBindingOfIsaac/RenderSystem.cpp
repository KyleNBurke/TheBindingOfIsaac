#include "stdafx.h"
#include "RenderSystem.hpp"

RenderSystem::RenderSystem(sf::RenderWindow& window) : window(window) {}

void RenderSystem::update(Entity& entity)
{
	//all entities will have a render component so no need to check, just draw it
	window.draw(entity.sprite);
}