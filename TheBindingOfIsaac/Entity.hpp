#pragma once

#include "stdafx.h"
#include "Component.hpp"

class Entity
{
public:
	Entity(sf::Sprite sprite);

	void move(sf::Vector2f amount);

	void addComponent(std::unique_ptr<Component> component);
	void removeComponent(Component& component);
	bool hasComponent(Component::ComponentType type) const;
	std::shared_ptr<Component> getComponent(Component::ComponentType type);

	sf::Sprite& getSprite();
	sf::Vector2f& getPosition();
	sf::FloatRect getEntityBounds() const;

	void setScale(float factorX, float factorY);
private:
	sf::Sprite sprite;
	sf::Vector2f position;
	std::vector<std::shared_ptr<Component>> components;
};

//A possible preformance increase would be to have hasComponent return an index and have getComponent take the index for one less interation cycle