#pragma once

#include "System.hpp"
#include "PlayerProjectileCom.hpp"

class ProjectileSystem : public System
{
public:
	ProjectileSystem(const sf::Time& deltaTime);

	void update(Entity& entity);

private:
	void removeProjectile(Entity& projectile);

	const sf::Time& deltaTime;
};