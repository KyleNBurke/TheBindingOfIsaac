#include "stdafx.h"
#include "InputSystem.hpp"
#include "Assemblages.hpp"
#include "Room.hpp"

InputSystem::InputSystem() {}

void InputSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::PlayerControlled))
	{
		std::shared_ptr<Component> component = entity.getComponent(Component::ComponentType::Velocity);
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

		std::shared_ptr<PlayerControlledCom> playerCom = std::dynamic_pointer_cast<PlayerControlledCom>(entity.getComponent(Component::ComponentType::PlayerControlled));

		if(playerCom->fireResetClock.getElapsedTime().asSeconds() >= playerCom->fireResetTime)
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

			length = std::sqrt(std::abs(direction.x) + std::abs(direction.y));
			if(length != 0)
			{
				direction /= length;

				Room::addEntityQueue.push_back(Assemblages::getInstance().createPlayerProjectile(entity.position, sf::Vector2f(500.0f * direction.x, 500.0f * direction.y)));

				playerCom->fireResetClock.restart();
			}


		}
	}
}