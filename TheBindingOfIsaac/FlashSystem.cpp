#include "stdafx.h"
#include "FlashSystem.hpp"
#include "HealthCom.hpp"

FlashSystem::FlashSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void FlashSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::Health))
	{
		std::shared_ptr<HealthCom> healthCom = std::dynamic_pointer_cast<HealthCom>(entity.getComponent(Component::ComponentType::Health));

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