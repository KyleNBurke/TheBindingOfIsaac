#pragma once

#include "System.hpp"
#include "ProjectileCom.hpp"

class ProjectileSystem : public System
{
public:
	ProjectileSystem(const sf::Time& deltaTime);

	void update(Entity& entity);

private:
	const sf::Time& deltaTime;
};