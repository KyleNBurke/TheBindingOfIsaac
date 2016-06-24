#pragma once

#include "System.hpp"

class ProjectileSystem : public System
{
public:
	ProjectileSystem(const sf::Time& deltaTime);

	void update(Entity& entity);

private:
	void applyDamage(Entity& entity, int damage);

	const sf::Time& deltaTime;
};