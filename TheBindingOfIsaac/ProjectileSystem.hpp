#pragma once

#include "System.hpp"
#include "ProjectileCom.hpp"
#include "AnimationCom.hpp"
#include "VelocityCom.hpp"
#include "LifetimeCom.hpp"

class ProjectileSystem : public System
{
public:
	ProjectileSystem(const sf::Time& deltaTime);

	void update(Entity& entity);

private:
	bool resolveTileCollisions(Entity& entity);
	bool resolveEnemyCollisions(Entity& projectile, std::shared_ptr<ProjectileCom> projCom);

	const sf::Time& deltaTime;
};