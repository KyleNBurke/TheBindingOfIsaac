#include "stdafx.h"
#include "ItemSystem.hpp"
#include "ItemCom.hpp"
#include "Floor.hpp"
#include "PlayerShotCom.hpp"

#include "GameplayState.hpp"
#include "HUD.hpp"
#include "Assemblages.hpp"
#include "HealthCom.hpp"


ItemSystem::ItemSystem(const sf::Time& deltaTime) : deltaTime(deltaTime), canPickupHeart(true), canPickupBomb(true) {}

void ItemSystem::update(Entity& entity)
{
	if(&Floor::getCurrentRoom() == &Floor::getRoom(4, 2) && &entity != &Floor::player)
	{
		if(entity.hasComponent(Component::ComponentType::Item))
		{
			std::shared_ptr<ItemCom> itemCom = std::dynamic_pointer_cast<ItemCom>(entity.getComponent(Component::ComponentType::Item));

			if(itemCom->itemType == ItemCom::ItemType::PlusOneHeart)
			{
				if(Floor::player.getBounds().intersects(entity.getBounds()) && GameplayState::getPlayerCoins() >= itemCom->price)
				{
					if(canPickupHeart)
					{
						GameplayState::updatePlayerCoins(-itemCom->price);

						int& health = std::dynamic_pointer_cast<HealthCom>(Floor::player.getComponent(Component::ComponentType::Health))->health;
						HUD::updatePlayerHealth(++health);

						canPickupHeart = false;
					}
				}
				else
					canPickupHeart = true;
			}
			else if(itemCom->itemType == ItemCom::ItemType::PlusOneBomb)
			{
				if(Floor::player.getBounds().intersects(entity.getBounds()) && GameplayState::getPlayerCoins() >= itemCom->price)
				{
					if(canPickupBomb)
					{
						GameplayState::updatePlayerCoins(-itemCom->price);

						GameplayState::updatePlayerBombs(1);

						canPickupBomb = false;
					}
				}
				else
					canPickupBomb = true;
			}
			else
			{
				if(Floor::player.getBounds().intersects(entity.getBounds()) && GameplayState::getPlayerCoins() >= itemCom->price)
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
						case ItemCom::ItemType::RangeUp:
							Assemblages::getInstance().playerProjectileLifetime += 0.2f;
							break;
						case ItemCom::ItemType::ProjectileBombs:
							Floor::player.addComponent(std::unique_ptr<Component>(new ItemCom(ItemCom::ItemType::ProjectileBombs)));
							break;
					}
				}
			}
		}





		/*if(entity.hasComponent(Component::ComponentType::Item) && Floor::player.getBounds().intersects(entity.getBounds()))
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
					case ItemCom::ItemType::RangeUp:
						Assemblages::getInstance().playerProjectileLifetime += 0.2f;
						break;
					case ItemCom::ItemType::ProjectileBombs:
						Floor::player.addComponent(std::unique_ptr<Component>(new ItemCom(ItemCom::ItemType::ProjectileBombs)));
						break;
					case ItemCom::ItemType::PlusOneHeart:
					{
						int& health = std::dynamic_pointer_cast<HealthCom>(Floor::player.getComponent(Component::ComponentType::Health))->health;
						HUD::updatePlayerHealth(++health);
						break;
					}
					case ItemCom::ItemType::PlusOneBomb:
						GameplayState::updatePlayerBombs(1);
						break;
				}
			}
		}*/

		/*
		if this has item component type
		{
			if it's the plus one heart
			{
				if player intersects it
				{
					if canPickup == true
					{
						pick it up
					}
				}
				else
					canPickup = true;
			}
			else
			{
				if player intersects it
				{
					do regular
				}
			}
		}
		*/
	}
}