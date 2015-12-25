#include "stdafx.h"
#include "PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::update(std::vector<Entity>& entities)
{
	for(std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		if(it->hasComponent(Component::ComponentType::Velocity))
		{
			std::shared_ptr<Component> component = it->getComponent(Component::ComponentType::Velocity);
			std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(component);

			velocityCom->getVelocity().x = (velocityCom->getVelocity().x + velocityCom->getAcceleration() * velocityCom->getDirection().x) * velocityCom->getDeceleration();
			velocityCom->getVelocity().y = (velocityCom->getVelocity().y + velocityCom->getAcceleration() * velocityCom->getDirection().y) * velocityCom->getDeceleration();
		}
	}
}