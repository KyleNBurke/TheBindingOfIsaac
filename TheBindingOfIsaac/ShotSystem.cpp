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
	}
	else if(entity.hasComponent(Component::ComponentType::JimmyShot))
	{
		std::shared_ptr<JimmyShotCom> shotCom = std::dynamic_pointer_cast<JimmyShotCom>(entity.getComponent(Component::ComponentType::JimmyShot));

		shotCom->currentShotTime += deltaTime.asSeconds();

		if(shotCom->currentShotTime >= shotCom->maxShotTime)
		{
			shotCom->currentShotTime = 0.0f;
			shotCom->maxShotTime = (float)std::rand() / (float)RAND_MAX * shotCom->randShotTimeAmount + 1.0f;

			sf::Vector2f direction = Floor::player.position - entity.position;
			float l = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			if(l != 0.0f)
				direction /= l;

			Floor::getCurrentRoom().addEntity(Assemblages::getInstance().createRegularProjectile(entity.position, direction * shotCom->projectileSpeed));
		}
	}
}