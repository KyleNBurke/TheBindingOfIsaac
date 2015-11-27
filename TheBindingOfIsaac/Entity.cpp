#include "stdafx.h"
#include "Entity.hpp"

Entity::Entity(sf::Sprite sprite) : sprite(sprite) {}

void Entity::move(sf::Vector2f amount)
{
	position += amount;
	sprite.setPosition(position);
}

void Entity::addComponent(std::unique_ptr<Component> component)
{
	components.push_back(std::move(component));
}

void Entity::removeComponent(Component& component)
{

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

const sf::Sprite& Entity::getSprite() const
{
	return sprite;
}

sf::Vector2f& Entity::getPosition()
{
	return position;
}

sf::FloatRect Entity::getEntityBounds() const
{
	return sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

void Entity::setScale(float factorX, float factorY)
{
	sprite.setScale(factorX, factorY);
}