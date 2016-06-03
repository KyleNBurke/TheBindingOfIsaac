#include "stdafx.h"
#include "Entity.hpp"

Entity::Entity(sf::Sprite sprite) : sprite(sprite) {}

void Entity::addComponent(std::unique_ptr<Component> component)
{
	components.push_back(std::move(component));
}

void Entity::removeComponent(Component& component)
{
	std::cout << "removeComponent() not implemented" << std::endl;
}

bool Entity::hasComponent(Component::ComponentType type) const
{
	for(std::vector<std::shared_ptr<Component>>::const_iterator it = components.begin(); it != components.end(); ++it)
		if((*it)->getType() == type)
			return true;

	return false;
}

std::shared_ptr<Component> Entity::getComponent(Component::ComponentType type)
{
	for(std::vector<std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end(); ++it)
		if((*it)->getType() == type)
			return *it;

	return std::shared_ptr<Component>();
}