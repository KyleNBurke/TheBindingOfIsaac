#include "stdafx.h"
#include "RenderSystem.hpp"



#include "PacMoveCom.hpp"

RenderSystem::RenderSystem(sf::RenderWindow& window) : window(window) {}

void RenderSystem::update(Entity& entity)
{
	window.draw(entity.sprite);
}