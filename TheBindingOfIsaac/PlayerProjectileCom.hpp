#pragma once

#include "stdafx.h"
#include "Component.hpp"
#include "Entity.hpp"

class PlayerProjectileCom : public Component
{
public:
	PlayerProjectileCom();

	void addProjectile(sf::Vector2f position, sf::Vector2f direction, std::vector<Entity>& entities);
	Component::ComponentType getType() const;

	//std::vector<Entity> projectiles;
	const static float velocityConst;
};