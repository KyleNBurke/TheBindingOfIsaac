#include "stdafx.h"
#include "FlashSystem.hpp"
#include "HealthCom.hpp"
#include "Floor.hpp"
#include "Assemblages.hpp"

FlashSystem::FlashSystem(const sf::Time& deltaTime) : deltaTime(deltaTime), maxPlayerFlashes(10), currPlayerFlashes(0) {}

void FlashSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::Health))
	{
		std::shared_ptr<HealthCom> healthCom = std::dynamic_pointer_cast<HealthCom>(entity.getComponent(Component::ComponentType::Health));

		if(&entity == &Floor::player)
		{
			if(healthCom->flashing)
			{
				healthCom->currFlashTime += deltaTime.asSeconds();
				
				if(healthCom->currFlashTime >= healthCom->maxFlashTime)
				{
					flip = !flip;
					if(flip)
					{
						Floor::player.sprite.setColor(sf::Color::White);
						Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createPlayerDamageStain(Floor::player.sprite.getPosition()));
					}
					else
						Floor::player.sprite.setColor(sf::Color::Black);

					healthCom->currFlashTime = 0.0f;
					currPlayerFlashes++;

					if(currPlayerFlashes > maxPlayerFlashes)
					{
						healthCom->flashing = false;
						healthCom->currFlashTime = 0.0f;
						currPlayerFlashes = 0;
						Floor::player.sprite.setColor(sf::Color::White);
					}

				}
			}
		}
		else
		{
			if(healthCom->flashing)
			{
				healthCom->currFlashTime += deltaTime.asSeconds();
				entity.sprite.setColor(sf::Color::Red);

				if(healthCom->currFlashTime >= healthCom->maxFlashTime)
				{
					healthCom->flashing = false;
					healthCom->currFlashTime = 0.0f;
					entity.sprite.setColor(sf::Color::White);
				}
			}
		}
	}
}