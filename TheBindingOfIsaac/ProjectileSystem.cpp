#include "stdafx.h"
#include "ProjectileSystem.hpp"

ProjectileSystem::ProjectileSystem() {}

void ProjectileSystem::update(std::vector<Entity>& entities)
{
	for(std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		/*if(it->hasComponent(Component::ComponentType::PlayerProjectileCom))
		{
			std::shared_ptr<Component> com = it->getComponent(Component::ComponentType::PlayerProjectileCom);
			std::shared_ptr<PlayerProjectileCom> projCom = std::dynamic_pointer_cast<PlayerProjectileCom>(com);

			for(std::vector<Entity>::iterator it = projCom->projectiles.begin(); it != projCom->projectiles.end(); ++it)
			{

			}
		}*/
	}
}