#include "stdafx.h"
#include "ShotSystem.hpp"
#include "PlayerShotCom.hpp"
#include "Utilities.hpp"
#include "Assemblages.hpp"
#include "Floor.hpp"
#include "Input.hpp"
#include <math.h>
#include "VelocityCom.hpp"
#include "JimmyShotCom.hpp"
#include "GameplayState.hpp"
#include "SpawnerShotCom.hpp"
#include "SpinShotCom.hpp"

ShotSystem::ShotSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void ShotSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::PlayerShot))
	{
		std::shared_ptr<PlayerShotCom> playerShotCom = std::dynamic_pointer_cast<PlayerShotCom>(entity.getComponent(Component::ComponentType::PlayerShot));
		std::shared_ptr<VelocityCom> playerVelCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));

		if(playerShotCom->fireResetClock.getElapsedTime().asSeconds() >= playerShotCom->fireResetTime)
		{
			sf::Vector2i direction;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::I))
			{
				direction.y -= 1;
				entity.sprite.setRotation(180.0f);
			}

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::K))
			{
				direction.y += 1;
				entity.sprite.setRotation(0.0f);
			}

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::J))
			{
				direction.x -= 1;
				direction.y = 0;
			}

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::L))
			{
				direction.x += 1;
				direction.y = 0;
			}

			if(direction.x != 0 || direction.y != 0)
			{
				sf::Vector2f velocity = 700.0f * (sf::Vector2f)direction + playerVelCom->velocity * 0.6f;

				float angle = std::atan(-velocity.y / velocity.x);

				if(velocity.x < 0)
					angle += 3.14159f;
				
				float randomRadAmount = 0.1f;
				angle += (float)std::rand() / (float)RAND_MAX * randomRadAmount - randomRadAmount / 2;

				float length = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
				velocity.x = std::cos(angle) * length;
				velocity.y = -std::sin(angle) * length;

				Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createPlayerProjectile(entity.sprite.getPosition(), velocity));

				playerShotCom->fireResetClock.restart();
			}
				
		}

		if(Input::getInstance().keyPressed(sf::Keyboard::Key::E) && GameplayState::getPlayerBombs() > 0)
		{
			GameplayState::updatePlayerBombs(-1);
			Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createPlayerBomb(entity.sprite.getPosition()));
		}
	}
	else if(entity.hasComponent(Component::ComponentType::JimmyShot))
	{
		std::shared_ptr<JimmyShotCom> shotCom = std::dynamic_pointer_cast<JimmyShotCom>(entity.getComponent(Component::ComponentType::JimmyShot));

		shotCom->currentShotTime += deltaTime.asSeconds();

		if(shotCom->currentShotTime >= shotCom->maxShotTime)
		{
			shotCom->currentShotTime = 0.0f;
			shotCom->maxShotTime = (float)std::rand() / (float)RAND_MAX * shotCom->randShotTimeAmount + 1.0f;

			if(shotCom->variation == JimmyShotCom::Variation::Direct)
			{
				sf::Vector2f direction = Floor::player.position - entity.position;
				float l = std::sqrt(direction.x * direction.x + direction.y * direction.y);
				if(l != 0.0f)
					direction /= l;

				Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createEnemyRegularProjectile(entity.position, direction * shotCom->projectileSpeed));
			}
			else
			{
				int amount = 6;
				for(int i = 0; i < amount; i++)
				{
					float directionDeg = 2 * 3.1415f / amount * i;
					sf::Vector2f direction(std::cos(directionDeg), std::sin(directionDeg));

					Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createEnemyRegularProjectile(entity.position, direction * shotCom->projectileSpeed));
				}
			}
		}
	}
	else if(entity.hasComponent(Component::ComponentType::SpawnerShot))
	{
		std::shared_ptr<SpawnerShotCom> shotCom = std::dynamic_pointer_cast<SpawnerShotCom>(entity.getComponent(Component::ComponentType::SpawnerShot));

		shotCom->currentShotTime += deltaTime.asSeconds();

		if(shotCom->currentShotTime >= shotCom->maxShotTime)
		{
			shotCom->currentShotTime = 0.0f;
			shotCom->maxShotTime = (float)std::rand() / (float)RAND_MAX * shotCom->randShotTimeAmount + 2.0f;

			switch(shotCom->variation)
			{
				case SpawnerShotCom::Variation::Attack:
					Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createAttackFly(entity.position));
					break;
				case SpawnerShotCom::Variation::Bomb:
					Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createBombFly(entity.position));
					break;
				case SpawnerShotCom::Variation::Daddy:
					Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createDaddyFly(entity.position));
					break;
			}
		}
	}
	else if(entity.hasComponent(Component::ComponentType::SpinShot))
	{
		std::shared_ptr<SpinShotCom> shotCom = std::dynamic_pointer_cast<SpinShotCom>(entity.getComponent(Component::ComponentType::SpinShot));

		shotCom->currentShotTime += deltaTime.asSeconds();

		if(shotCom->currentShotTime >= shotCom->maxShotTime)
		{
			shotCom->currentShotTime = 0.0f;

			float directionDeg = 2 * 3.1415f / shotCom->shotAmount * shotCom->shotIndex;
			sf::Vector2f direction(std::cos(directionDeg), std::sin(directionDeg));
			shotCom->shotIndex = shotCom->shotIndex++ % shotCom->shotAmount;

			if(shotCom->variation == SpinShotCom::Variation::Regular)
				Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createEnemyRegularProjectile(entity.position, direction * shotCom->shotSpeed));
			else
				Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createEnemySlideBomb(entity.position, direction * shotCom->shotSpeed));
		}
	}
}