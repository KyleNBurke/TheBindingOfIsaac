#include "stdafx.h"
#include "RenderSystem.hpp"

RenderSystem::RenderSystem(sf::RenderWindow& window) : window(window) {}

void RenderSystem::update(std::vector<Entity>& entities)
{
	for(std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		//all entities will have a render component so no need to check, just draw it
		window.draw(it->getSprite());
	}
}