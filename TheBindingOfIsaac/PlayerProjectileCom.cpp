#include "stdafx.h"
#include "PlayerProjectileCom.hpp"
#include "Assemblages.hpp"

const float PlayerProjectileCom::velocityConst = 300.0f;

PlayerProjectileCom::PlayerProjectileCom() {}

void PlayerProjectileCom::addProjectile(sf::Vector2f position, sf::Vector2f direction, std::vector<Entity>& entities)
{
	/*Entity projectile = Assemblages::getInstance().createProjectile();
	std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(projectile.getComponent(Component::ComponentType::Velocity));
	velocityCom->getDirection() = direction;
	velocityCom->getVelocity() = sf::Vector2f(velocityConst * direction.x, velocityConst * direction.y);

	//projectiles.push_back(projectile);
	entities.push_back(projectile);*/
}

Component::ComponentType PlayerProjectileCom::getType() const
{
	return Component::ComponentType::PlayerProjectileCom;
}