#pragma once

#include "stdafx.h"
#include "Component.hpp"

class Entity
{
public:
	Entity();
	Entity(sf::Sprite sprite, sf::Vector2f position, int drawPriority);
	Entity(sf::Sprite sprite, sf::Vector2f position, sf::IntRect bounds, int drawPriority);

	sf::FloatRect getBounds() const;
	void addComponent(std::unique_ptr<Component> component);
	void removeComponent(Component& component);
	bool hasComponent(Component::ComponentType type) const;
	std::shared_ptr<Component> getComponent(Component::ComponentType type);

	sf::Sprite sprite;
	sf::Vector2f position;
	bool shouldDelete;
	int drawPriority;

private:
	sf::IntRect bounds;
	std::vector<std::shared_ptr<Component>> components;
};

//A possible preformance increase would be to have hasComponent return an index and have getComponent take the index for one less interation cycle