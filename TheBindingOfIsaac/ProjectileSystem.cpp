#include "stdafx.h"
#include "ProjectileSystem.hpp"
#include "PlayerProjectileCom.hpp"
#include "EnemyProjectileCom.hpp"
#include "Map.hpp"
#include "HealthCom.hpp"

ProjectileSystem::ProjectileSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void ProjectileSystem::update(Entity& entity)
{
	bool playerProjectile = entity.hasComponent(Component::ComponentType::PlayerProjectile);
	bool enemyProjectile = entity.hasComponent(Component::ComponentType::EnemyProjectile);

	if(playerProjectile || enemyProjectile)
	{
		sf::FloatRect entityBounds = entity.sprite.getGlobalBounds();
		int scale = Room::tileSize * Utilities::getInstance().getScale();

		if(entityBounds.left < 0.0f ||
			entityBounds.top < 0.0f ||
			entityBounds.left + entityBounds.width > Room::width * scale ||
			entityBounds.top + entityBounds.height > Room::height * scale)
		{
			entity.shouldDelete = true;
		}
		else
		{
			int left = (int)(std::floorf(entityBounds.left / scale));
			int right = (int)(std::ceilf((entityBounds.left + entityBounds.width) / scale)) - 1;
			int top = (int)(std::floorf(entityBounds.top / scale));
			int bottom = (int)(std::ceilf((entityBounds.top + entityBounds.height) / scale)) - 1;

			for(int x = left; x <= right; x++)
				for(int y = top; y <= bottom; y++)
					if(Map::getCurrentRoom().getTileType(x, y) == Room::TileType::wall)
						entity.shouldDelete = true;
		}
	}

	if(playerProjectile)
	{
		for(std::vector<Entity>::iterator it = Map::getCurrentRoom().entities.begin(); it != Map::getCurrentRoom().entities.end(); ++it)
		{
			bool intersects = entity.sprite.getGlobalBounds().intersects(it->sprite.getGlobalBounds());
			if(it->hasComponent(Component::ComponentType::Health) && intersects)
			{
				entity.shouldDelete = true;
				std::shared_ptr<PlayerProjectileCom> playerProjCom = std::dynamic_pointer_cast<PlayerProjectileCom>(entity.getComponent(Component::ComponentType::PlayerProjectile));
				applyDamage(*it, playerProjCom->damage);
				break;
			}
		}
	}

	if(enemyProjectile)
	{
		if(entity.sprite.getGlobalBounds().intersects(Map::player.sprite.getGlobalBounds()))
		{
			entity.shouldDelete = true;
			applyDamage(Map::player, 1);
		}
	}
}

void ProjectileSystem::applyDamage(Entity& entity, int damage)
{
	std::shared_ptr<HealthCom> healthCom = std::dynamic_pointer_cast<HealthCom>(entity.getComponent(Component::ComponentType::Health));
	healthCom->health -= damage;

	if(healthCom->health <= 0)
		entity.shouldDelete = true;
}