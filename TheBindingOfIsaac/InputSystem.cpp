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

			velocityCom->getDirection().x = 0;
			velocityCom->getDirection().y = 0;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::W))
				velocityCom->getDirection().y = -1;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::S))
				velocityCom->getDirection().y = 1;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::A))
				velocityCom->getDirection().x = -1;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::D))
				velocityCom->getDirection().x = 1;

		}
	}
}