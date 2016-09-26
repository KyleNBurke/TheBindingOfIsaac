#include "stdafx.h"
#include "InputSystem.hpp"
#include "VelocityCom.hpp"
#include "Utilities.hpp"
#include "AccelerationCom.hpp"
#include "PlayerControlledCom.hpp"

InputSystem::InputSystem() {}

void InputSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::PlayerControlled))
	{
		//std::shared_ptr<Component> component = entity.getComponent(Component::ComponentType::Velocity);
		//std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(component);

		/*velocityCom->direction.x = 0;
		velocityCom->direction.y = 0;

		if(Input::getInstance().keyHeld(sf::Keyboard::Key::W))
		{
			velocityCom->direction.y -= 1;
			entity.sprite.setRotation(180.0f);
		}

		if(Input::getInstance().keyHeld(sf::Keyboard::Key::S))
		{
			velocityCom->direction.y += 1;
			entity.sprite.setRotation(0.0f);
		}

		if(Input::getInstance().keyHeld(sf::Keyboard::Key::A))
			velocityCom->direction.x -= 1;

		if(Input::getInstance().keyHeld(sf::Keyboard::Key::D))
			velocityCom->direction.x += 1;

		float length = std::sqrt(std::abs(velocityCom->direction.x) + std::abs(velocityCom->direction.y));
		if(length != 0)
			velocityCom->direction /= length;*/


		std::shared_ptr<AccelerationCom> accelCom = std::dynamic_pointer_cast<AccelerationCom>(entity.getComponent(Component::ComponentType::AccelDecel));
		std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));
		std::shared_ptr<PlayerControlledCom> playerCom = std::dynamic_pointer_cast<PlayerControlledCom>(entity.getComponent(Component::ComponentType::PlayerControlled));

		accelCom->acceleration = sf::Vector2f();
		sf::Vector2f direction;

		if(Input::getInstance().keyHeld(sf::Keyboard::Key::W))
		{
			direction.y = -1.0f;
			entity.sprite.setRotation(180.0f);
		}

		if(Input::getInstance().keyHeld(sf::Keyboard::Key::S))
		{
			direction.y = 1.0f;
			entity.sprite.setRotation(0.0f);
		}

		if(Input::getInstance().keyHeld(sf::Keyboard::Key::A))
			direction.x = -1.0f;

		if(Input::getInstance().keyHeld(sf::Keyboard::Key::D))
			direction.x = 1.0f;

		float length = std::sqrt(std::abs(direction.x) + std::abs(direction.y));
		if(length != 0)
			direction /= length;

		accelCom->acceleration = (direction * playerCom->maxSpeed - velocityCom->velocity) *playerCom->acceleration;
		
	}
}