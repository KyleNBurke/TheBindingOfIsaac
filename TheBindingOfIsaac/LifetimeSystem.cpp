#include "stdafx.h"
#include "LifetimeSystem.hpp"
#include "LifetimeCom.hpp"
#include "Floor.hpp"
#include "Assemblages.hpp"
#include "ProjectileCom.hpp"

LifetimeSystem::LifetimeSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void LifetimeSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::Lifetime))
	{
		std::shared_ptr<LifetimeCom> lifetimeCom = std::dynamic_pointer_cast<LifetimeCom>(entity.getComponent(Component::ComponentType::Lifetime));

		lifetimeCom->elapsedTime += deltaTime.asSeconds();

		if(lifetimeCom->elapsedTime > lifetimeCom->lifetime)
		{
			entity.shouldDelete = true;

			if(entity.hasComponent(Component::ComponentType::Projectile))
			{
				Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createProjectileDeath(entity.sprite.getPosition()));
				std::shared_ptr<ProjectileCom> projCom = std::dynamic_pointer_cast<ProjectileCom>(entity.getComponent(Component::ComponentType::Projectile));

				if(projCom->projectileVariation == ProjectileCom::ProjectileVariation::Bomb)
				{
					Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createExplosion(entity.sprite.getPosition()));
					Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createExplosionStain(entity.sprite.getPosition()));

					if(projCom->projectileType == ProjectileCom::ProjectileType::Player)
					{
						for(std::vector<Entity>::iterator it = Floor::getCurrentRoom().getEntities().begin(); it != Floor::getCurrentRoom().getEntities().end(); ++it)
						{
							float distance = std::sqrt(std::powf((it->position.x - entity.position.x), 2) + std::powf((it->position.y - entity.position.y), 2));

							if(it->hasComponent(Component::ComponentType::Health) && distance < Utilities::getInstance().getScale() * Room::tileSize * 2.0f)
								Floor::getCurrentRoom().killEnemy(*it);
						}
					}
					else
					{
						float distance = std::sqrt(std::powf((Floor::player.position.x - entity.position.x), 2) + std::powf((Floor::player.position.y - entity.position.y), 2));

						if(distance < Utilities::getInstance().getScale() * Room::tileSize * 2.0f)
							Floor::damagePlayer(2);
					}
				}
			}
		}
	}
}