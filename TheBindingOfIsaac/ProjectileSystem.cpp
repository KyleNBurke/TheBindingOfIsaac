#include "stdafx.h"
#include "ProjectileSystem.hpp"
#include "Floor.hpp"
#include "HealthCom.hpp"
#include "AnimationStateDynamic.hpp"
#include "Assemblages.hpp"
#include "BouncerCom.hpp"
#include "VelocityCom.hpp"
#include "GameplayState.hpp"

ProjectileSystem::ProjectileSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void ProjectileSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::Projectile))
	{
		std::shared_ptr<ProjectileCom> projCom = std::dynamic_pointer_cast<ProjectileCom>(entity.getComponent(Component::ComponentType::Projectile));

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
		Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createProjectileDeath(entity.sprite.getPosition()));
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
				Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createProjectileDeath(entity.sprite.getPosition()));
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
		for(std::vector<Entity>::iterator it = Floor::getCurrentRoom().getEntities().begin(); it != Floor::getCurrentRoom().getEntities().end(); ++it)
		{
			bool intersects = projectile.getBounds().intersects(it->getBounds());
			if(it->hasComponent(Component::ComponentType::Health) && intersects)
			{
				projectile.shouldDelete = true;

				std::shared_ptr<HealthCom> healthCom = std::dynamic_pointer_cast<HealthCom>(it->getComponent(Component::ComponentType::Health));
				healthCom->health -= 1;

				Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createEnemyDamageStain(it->sprite.getPosition()));

				if(healthCom->health <= 0)
				{
					it->shouldDelete = true;
					Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createEnemyDeath(it->sprite.getPosition()));
					//Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createEnemyDeathStain(it->sprite.getPosition()));
					sf::Vector2f velocity;
					if(it->hasComponent(Component::ComponentType::Velocity))
					{
						velocity = std::dynamic_pointer_cast<VelocityCom>(it->getComponent(Component::ComponentType::Velocity))->velocity;
					}

					if(it->hasComponent(Component::ComponentType::Bouncer))
					{
						float speed = std::dynamic_pointer_cast<BouncerCom>(it->getComponent(Component::ComponentType::Bouncer))->projectileSpeed;

						Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createRegularProjectile(it->sprite.getPosition(), sf::Vector2f(-1, -1) / (float)sqrt(2) * speed));
						Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createRegularProjectile(it->sprite.getPosition(), sf::Vector2f(1, -1) / (float)sqrt(2) * speed));
						Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createRegularProjectile(it->sprite.getPosition(), sf::Vector2f(1, 1) / (float)sqrt(2) * speed));
						Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createRegularProjectile(it->sprite.getPosition(), sf::Vector2f(-1, 1) / (float)sqrt(2) * speed));
					}

					GameplayState::givePlayerCoins(1);
				}

				healthCom->flashing = true;

				return true;
			}
		}
	}
	else
	{
		if(projectile.getBounds().intersects(Floor::player.getBounds()))
		{
			projectile.shouldDelete = true;

			std::shared_ptr<HealthCom> healthCom = std::dynamic_pointer_cast<HealthCom>(Floor::player.getComponent(Component::ComponentType::Health));
			healthCom->health -= 1;
			healthCom->flashing = true;
		}

	}

	return false;
}