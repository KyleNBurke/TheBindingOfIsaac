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

			velocityCom->getDirection().x = 0;
			velocityCom->getDirection().y = 0;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::W))
				velocityCom->getDirection().y -= 1;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::S))
				velocityCom->getDirection().y += 1;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::A))
				velocityCom->getDirection().x -= 1;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::D))
				velocityCom->getDirection().x += 1;

			float length = std::sqrt(std::abs(velocityCom->getDirection().x) + std::abs(velocityCom->getDirection().y));
			if(length != 0)
				velocityCom->getDirection() /= length;

			sf::Vector2f direction;

			if(Input::getInstance().keyHeld(sf::Keyboard::Key::I))
				direction.y = 1;

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
				
				//std::shared_ptr<Component> com = it->getComponent(Component::ComponentType::PlayerProjectileCom);
				//std::shared_ptr<PlayerProjectileCom> projCom = std::dynamic_pointer_cast<PlayerProjectileCom>(com);

				//projCom->addProjectile(it->getPosition(), direction, entities);
				sf::Vector2f velocity(PlayerProjectileCom::velocityConst * direction.x, PlayerProjectileCom::velocityConst * direction.y);
				entityQueue.push_back(Assemblages::getInstance().createProjectile(it->getPosition(), velocity));
			}
		}
	}
}