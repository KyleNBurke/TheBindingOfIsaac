#include "stdafx.h"
#include "ItemSystem.hpp"
#include "VelocityCom.hpp"
#include "AccelerationCom.hpp"

ItemSystem::ItemSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void ItemSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::Item))
	{
		
	}
}