#include "stdafx.h"
#include "RenderSystem.hpp"

#include "Floor.hpp"
#include "ItemCom.hpp"

RenderSystem::RenderSystem(sf::RenderWindow& window) : window(window) {}

void RenderSystem::update(Entity& entity)
{
	window.draw(entity.sprite);

	if(&Floor::getCurrentRoom() == &Floor::getRoom(4, 2) && entity.hasComponent(Component::ComponentType::Item))
			window.draw(std::dynamic_pointer_cast<ItemCom>(entity.getComponent(Component::ComponentType::Item))->priceText);
}