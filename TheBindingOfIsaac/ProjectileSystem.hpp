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
	bool detectTileCollisions(Entity& entity);
	bool detectEntityCollisions(Entity& entity, std::shared_ptr<ProjectileCom> projCom);
	void applyDamage(Entity& entity, int damage);
	void removeProjectile(Entity& entity,
		std::shared_ptr<ProjectileCom> projCom,
		std::shared_ptr<AnimationCom> animCom,
		std::shared_ptr<VelocityCom> velCom,
		std::shared_ptr<LifetimeCom> lifetimeCom);

	const sf::Time& deltaTime;
};