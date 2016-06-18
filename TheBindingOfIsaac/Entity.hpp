#pragma once

#include "stdafx.h"
#include "Component.hpp"

class Entity
{
public:
	Entity(sf::Sprite sprite);

	void addComponent(std::unique_ptr<Component> component);
	void removeComponent(Component& component);
	bool hasComponent(Component::ComponentType type) const;
	std::shared_ptr<Component> getComponent(Component::ComponentType type);

	bool operator==(const Entity& entity) const;

	sf::Sprite sprite;
	sf::Vector2f position;
	bool shouldDelete;

private:
	std::vector<std::shared_ptr<Component>> components;
};

//A possible preformance increase would be to have hasComponent return an index and have getComponent take the index for one less interation cycle