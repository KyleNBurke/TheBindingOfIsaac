#include "stdafx.h"
#include "ItemSystem.hpp"
#include "ItemCom.hpp"
#include "Floor.hpp"
#include "PlayerShotCom.hpp"

#include "GameplayState.hpp"
#include "HUD.hpp"

ItemSystem::ItemSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void ItemSystem::update(Entity& entity)
{
	if(&Floor::getCurrentRoom() == &Floor::getRoom(4, 2))
	{
		if(entity.hasComponent(Component::ComponentType::Item) && Floor::player.getBounds().intersects(entity.getBounds()))
		{
			std::shared_ptr<ItemCom> itemCom = std::dynamic_pointer_cast<ItemCom>(entity.getComponent(Component::ComponentType::Item));
			
			if(GameplayState::getPlayerCoins() >= itemCom->price)
			{
				GameplayState::updatePlayerCoins(-itemCom->price);
				entity.shouldDelete = true;

				HUD::showPickupItemMessage(entity);

				switch(itemCom->itemType)
				{
					case ItemCom::ItemType::ROF_Up:
						std::dynamic_pointer_cast<PlayerShotCom>(Floor::player.getComponent(Component::ComponentType::PlayerShot))->fireResetTime = 0.1f;
						break;
					case ItemCom::ItemType::PlusTenBombs:
						GameplayState::updatePlayerBombs(10);
						break;
				}
			}
		}
	}
}