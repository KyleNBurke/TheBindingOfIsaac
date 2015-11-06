#include "stdafx.h"
#include "PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void PhysicsSystem::update(std::vector<Entity>& entities)
{
	for(std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		if(it->hasComponent(Component::ComponentType::Velocity))
		{
			std::shared_ptr<Component> component = it->getComponent(Component::ComponentType::Velocity);
			std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(component);

			velocityCom->velocity.x = (velocityCom->velocity.x + velocityCom->acceleration * velocityCom->direction.x) * velocityCom->deceleration;
			velocityCom->velocity.y = (velocityCom->velocity.y + velocityCom->acceleration * velocityCom->direction.y) * velocityCom->deceleration;

			it->move(velocityCom->velocity * deltaTime.asSeconds());
		}
	}
}