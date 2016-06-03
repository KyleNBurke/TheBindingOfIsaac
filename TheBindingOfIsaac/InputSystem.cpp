#include "stdafx.h"
#include "InputSystem.hpp"
#include "Assemblages.hpp"

InputSystem::InputSystem(std::vector<Entity>& entityQueue) : entityQueue(entityQueue) {}

void InputSystem::update(std::vector<Entity>& entities)
{
	for(std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		if(it->hasComponent(Component::ComponentType::PlayerControlled))
		{
			std::shared_ptr<Component> component = it->getComponent(Component::ComponentType::Velocity);
			std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(component);

			velocityCom->direction.x = 0;
			velocityCom->direction.y = 0;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::W))
				velocityCom->direction.y -= 1;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::S))
				velocityCom->direction.y += 1;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::A))
				velocityCom->direction.x -= 1;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::D))
				velocityCom->direction.x += 1;

			float length = std::sqrt(std::abs(velocityCom->direction.x) + std::abs(velocityCom->direction.y));
			if(length != 0)
				velocityCom->direction /= length;

			sf::Vector2f direction;

			if(PlayerProjectileCom::fireResetClock.getElapsedTime().asSeconds() >= PlayerProjectileCom::fireResetTime)
			{
				if(Input::getInstance().keyHeld(sf::Keyboard::Key::I))
					direction.y = -1;

				if(Input::getInstance().keyHeld(sf::Keyboard::Key::K))
					direction.y = 1;

				if(Input::getInstance().keyHeld(sf::Keyboard::Key::J))
					direction.x = -1;

				if(Input::getInstance().keyHeld(sf::Keyboard::Key::L))
					direction.x = 1;

				length = std::sqrt(std::abs(direction.x) + std::abs(direction.y));
				if(length != 0)
				{
					direction /= length;

					sf::Vector2f velocity(PlayerProjectileCom::velocityConst * direction.x, PlayerProjectileCom::velocityConst * direction.y);
					entityQueue.push_back(Assemblages::getInstance().createProjectile(it->position, velocity));

					PlayerProjectileCom::fireResetClock.restart();
				}
			}
		}
	}
}