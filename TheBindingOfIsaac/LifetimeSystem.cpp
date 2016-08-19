#include "stdafx.h"
#include "LifetimeSystem.hpp"
#include "LifetimeCom.hpp"
#include "Floor.hpp"
#include "Assemblages.hpp"

LifetimeSystem::LifetimeSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void LifetimeSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::Lifetime))
	{
		std::shared_ptr<LifetimeCom> lifetimeCom = std::dynamic_pointer_cast<LifetimeCom>(entity.getComponent(Component::ComponentType::Lifetime));

		lifetimeCom->elapsedTime += deltaTime.asSeconds();

		if(lifetimeCom->elapsedTime > lifetimeCom->lifetime)
		{
			entity.shouldDelete = true;

			if(entity.hasComponent(Component::ComponentType::Projectile))
				Floor::getCurrentRoom().addEntityQueue.push_back(Assemblages::getInstance().createProjectileDeath(entity.sprite.getPosition()));

		}
	}
}