#include "stdafx.h"
#include "ProjectileSystem.hpp"
#include "Map.hpp"
#include "VelocityCom.hpp"

ProjectileSystem::ProjectileSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void ProjectileSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::PlayerProjectileCom))
	{
		sf::FloatRect entityBounds = entity.sprite.getGlobalBounds();
		int scale = Room::tileSize * Utilities::getInstance().getScale();

		if(entityBounds.left < scale ||
			entityBounds.top < scale ||
			entityBounds.left + entityBounds.width > (Room::width + 1) * scale ||
			entityBounds.top + entityBounds.height >(Room::height + 1) * scale)
		{
			removeProjectile(entity);
		}

		int left = (int)(std::floorf(entityBounds.left / scale));
		int right = (int)(std::ceilf((entityBounds.left + entityBounds.width) / scale)) - 1;
		int top = (int)(std::floorf(entityBounds.top / scale));
		int bottom = (int)(std::ceilf((entityBounds.top + entityBounds.height) / scale)) - 1;
	}
}

void ProjectileSystem::removeProjectile(Entity& projectile) {
	Room::removeEntityQueue.push_back(std::unique_ptr<Entity>(&projectile));
}