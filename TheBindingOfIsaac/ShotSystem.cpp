#include "stdafx.h"
#include "ShotSystem.hpp"
#include "TurretShotCom.hpp"
#include "PlayerShotCom.hpp"
#include "Utilities.hpp"
#include "Assemblages.hpp"
#include "Room.hpp"
#include "Input.hpp"

ShotSystem::ShotSystem() {}

void ShotSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::PlayerShot))
	{
		std::shared_ptr<PlayerShotCom> playerShotCom = std::dynamic_pointer_cast<PlayerShotCom>(entity.getComponent(Component::ComponentType::PlayerShot));

		if(playerShotCom->fireResetClock.getElapsedTime().asSeconds() >= playerShotCom->fireResetTime)
		{
			sf::Vector2f direction;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::I))
				direction.y -= 1;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::K))
				direction.y += 1;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::J))
				direction.x -= 1;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::L))
				direction.x += 1;

			float length = std::sqrt(std::abs(direction.x) + std::abs(direction.y));
			if(length != 0)
			{
				direction /= length;

				Room::addEntityQueue.push_back(Assemblages::getInstance().createPlayerProjectile(entity.position, sf::Vector2f(500.0f * direction.x, 500.0f * direction.y)));

				playerShotCom->fireResetClock.restart();
			}


		}
	}

	if(entity.hasComponent(Component::ComponentType::TurretShot))
	{
		std::shared_ptr<TurretShotCom> turret = std::dynamic_pointer_cast<TurretShotCom>(entity.getComponent(Component::ComponentType::TurretShot));

		if(turret->timer.getElapsedTime().asSeconds() >= turret->shotTime)
		{
			sf::FloatRect bounds = entity.sprite.getGlobalBounds();
			float scale = (float)Utilities::getInstance().getScale();
			sf::Vector2f pos(bounds.left + scale, bounds.top + scale);

			sf::Vector2f dir1, dir2, dir3, dir4;

			if(turret->flip)
			{
				dir1.y = -1.0f;
				dir2.y = +1.0f;
				dir3.x = -1.0f;
				dir4.x = +1.0f;
			}
			else
			{
				float c = std::sqrt(0.5f);

				dir1.x = -c; dir1.y = -c;
				dir2.x = +c; dir2.y = -c;
				dir3.x = +c; dir3.y = +c;
				dir4.x = -c; dir4.y = +c;
			}

			Entity p1 = Assemblages::getInstance().createRegularProjectile(pos, turret->projectileSpeed * dir1);
			Entity p2 = Assemblages::getInstance().createRegularProjectile(pos, turret->projectileSpeed * dir2);
			Entity p3 = Assemblages::getInstance().createRegularProjectile(pos, turret->projectileSpeed * dir3);
			Entity p4 = Assemblages::getInstance().createRegularProjectile(pos, turret->projectileSpeed * dir4);

			Room::addEntityQueue.push_back(p1);
			Room::addEntityQueue.push_back(p2);
			Room::addEntityQueue.push_back(p3);
			Room::addEntityQueue.push_back(p4);

			turret->timer.restart();
			turret->flip = !turret->flip;
		}
	}
}