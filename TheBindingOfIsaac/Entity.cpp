#include "stdafx.h"
#include "Entity.hpp"
#include "Utilities.hpp"

Entity::Entity(sf::Sprite sprite) : Entity(sprite, (sf::IntRect)sprite.getLocalBounds()) {}

Entity::Entity(sf::Sprite sprite, sf::IntRect bounds) : sprite(sprite), bounds(bounds), shouldDelete(false) {}

sf::FloatRect Entity::getBounds() const
{
	sf::Vector2f pos = sprite.getPosition();
	float scale = (float)Utilities::getInstance().getScale();
	return sf::FloatRect(pos.x + (float)bounds.left * scale, pos.y + (float)bounds.top * scale, (float)bounds.width * scale, (float)bounds.height * scale);
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