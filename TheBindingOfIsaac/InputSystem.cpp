#include "stdafx.h"
#include "InputSystem.hpp"

InputSystem::InputSystem() {}

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
				velocityCom->direction.y = -1;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::S))
				velocityCom->direction.y = 1;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::A))
				velocityCom->direction.x = -1;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::D))
				velocityCom->direction.x = 1;

		}
	}
}