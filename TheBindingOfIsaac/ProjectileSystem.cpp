#include "stdafx.h"
#include "ProjectileSystem.hpp"
#include "Floor.hpp"
#include "HealthCom.hpp"
#include "AnimationStateDynamic.hpp"
#include "Assemblages.hpp"

ProjectileSystem::ProjectileSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void ProjectileSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::Projectile))
	{
		std::shared_ptr<ProjectileCom> projCom = std::dynamic_pointer_cast<ProjectileCom>(entity.getComponent(Component::ComponentType::Projectile));

		/*lifetimeCom->elapsedTime += deltaTime.asSeconds();

		if(projCom->alive)
		{
			if(lifetimeCom->elapsedTime >= lifetimeCom->lifetime)
			{
				removeProjectile(entity, projCom, animCom, velCom, lifetimeCom);
				return;
			}

			if(detectTileCollisions(entity))
			{
				removeProjectile(entity, projCom, animCom, velCom, lifetimeCom);
				return;
			}

			if(detectEntityCollisions(entity, projCom))
			{
				entity.shouldDelete = true;
			}
		}
		else
		{
			if(lifetimeCom->elapsedTime >= state->frameCount * state->frameTime)
				entity.shouldDelete = true;
		}*/

		if(resolveTileCollisions(entity))
			return;

		if(resolveEnemyCollisions(entity, projCom))
			return;
	}
}

bool ProjectileSystem::resolveTileCollisions(Entity& entity)
{
	int scale = Room::tileSize * Utilities::getInstance().getScale();
	sf::FloatRect entityBounds = entity.getBounds();

	if(entityBounds.left < 0.0f ||
		entityBounds.top < 0.0f ||
		entityBounds.left + entityBounds.width > Room::width * scale ||
		entityBounds.top + entityBounds.height > Room::height * scale)
	{
		entity.shouldDelete = true;
		Floor::getCurrentRoom().addEntityQueue.push_back(Assemblages::getInstance().createProjectileDeath(entity.sprite.getPosition()));
		return true;
	}
	

	int left = (int)(std::floorf(entityBounds.left / scale));
	int right = (int)(std::ceilf((entityBounds.left + entityBounds.width) / scale)) - 1;
	int top = (int)(std::floorf(entityBounds.top / scale));
	int bottom = (int)(std::ceilf((entityBounds.top + entityBounds.height) / scale)) - 1;

	for(int x = left; x <= right; x++)
	{
		for(int y = top; y <= bottom; y++)
		{
			if(Floor::getCurrentRoom().getTileType(x, y) == Room::TileType::wall)
			{
				entity.shouldDelete = true;
				Floor::getCurrentRoom().addEntityQueue.push_back(Assemblages::getInstance().createProjectileDeath(entity.sprite.getPosition()));
				return true;
			}
		}
	}

	return false;
}

bool ProjectileSystem::resolveEnemyCollisions(Entity& projectile, std::shared_ptr<ProjectileCom> projCom)
{
	if(projCom->projectileType == ProjectileCom::ProjectileType::Player)
	{
		for(std::vector<Entity>::iterator it = Floor::getCurrentRoom().entities.begin(); it != Floor::getCurrentRoom().entities.end(); ++it)
		{
			bool intersects = projectile.getBounds().intersects(it->sprite.getGlobalBounds());
			if(it->hasComponent(Component::ComponentType::Health) && intersects)
			{
				projectile.shouldDelete = true;

				std::shared_ptr<HealthCom> healthCom = std::dynamic_pointer_cast<HealthCom>(it->getComponent(Component::ComponentType::Health));
				healthCom->health -= 1;

				Floor::getCurrentRoom().addEntityQueue.push_back(Assemblages::getInstance().createEnemyDamageStain(it->sprite.getPosition()));

				if(healthCom->health <= 0)
				{
					it->shouldDelete = true;
					Floor::getCurrentRoom().addEntityQueue.push_back(Assemblages::getInstance().createEnemyDeath(it->sprite.getPosition()));
					Floor::getCurrentRoom().addEntityQueue.push_back(Assemblages::getInstance().createEnemyDeathStain(it->sprite.getPosition()));
				}

				healthCom->flashing = true;

				return true;
			}
		}
	}
	/*else
	{
		//The projecile is an Enemy one
	}*/

	return false;
}