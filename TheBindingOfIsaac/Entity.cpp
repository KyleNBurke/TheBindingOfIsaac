#include "stdafx.h"
#include "Entity.hpp"
#include "Utilities.hpp"

Entity::Entity() : Entity(sf::Sprite(), 0) {}

Entity::Entity(sf::Sprite sprite, int drawPriority) : Entity(sprite, (sf::IntRect)sprite.getLocalBounds(), drawPriority) {}

Entity::Entity(sf::Sprite sprite, sf::IntRect bounds, int drawPriority) : sprite(sprite), bounds(bounds), drawPriority(drawPriority), shouldDelete(false) {}

sf::FloatRect Entity::getBounds() const
{
	return sprite.getTransform().transformRect((sf::FloatRect)bounds);
}

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