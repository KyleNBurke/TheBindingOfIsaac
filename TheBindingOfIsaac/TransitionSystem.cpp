#include "stdafx.h"
#include "TransitionSystem.hpp"
#include "Utilities.hpp"
#include "GameManager.hpp"
#include "Floor.hpp"
#include "VelocityCom.hpp"

TransitionSystem::TransitionSystem(const sf::Time& deltaTime, HUD& hud) :
	deltaTime(deltaTime), transitioning(false), time(0.0f), transitionTime(0.5f), updated(false), playerPosX(4), playerPosY(2), hud(hud)
{
	int scale = Utilities::getInstance().getScale() * Room::tileSize;
	rectangleShape.setSize(sf::Vector2f((float)(Room::width * scale), (float)(Room::height * scale)));
	rectangleShape.setFillColor(sf::Color::Black);
}

void TransitionSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::PlayerControlled))
	{
		if(!transitioning)
		{
			std::shared_ptr<VelocityCom> velCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));
			sf::FloatRect bounds = entity.sprite.getGlobalBounds();
			int scale = Utilities::getInstance().getScale() * Room::tileSize;

			if(bounds.top < 0.0f)
			{
				transitioning = true;
				playerPosY--;
				position = sf::Vector2f(Floor::player.sprite.getPosition().x, Room::height * scale - (float)scale / 2.0f);
				velCom->velocity = sf::Vector2f();
			}
			else if(bounds.top + bounds.height > Room::height * scale)
			{
				transitioning = true;
				playerPosY++;
				position = sf::Vector2f(Floor::player.sprite.getPosition().x, (float)scale / 2.0f);
				velCom->velocity = sf::Vector2f();
			}
			else if(bounds.left < 0.0f)
			{
				transitioning = true;
				playerPosX--;
				position = sf::Vector2f(Room::width * scale - (float)scale / 2.0f, Floor::player.sprite.getPosition().y);
				velCom->velocity = sf::Vector2f();
			}
			else if(bounds.left + bounds.width > Room::width * scale)
			{
				transitioning = true;
				playerPosX++;
				position = sf::Vector2f((float)scale / 2.0f, Floor::player.sprite.getPosition().y);
				velCom->velocity = sf::Vector2f();
			}
		}

		if(transitioning)
		{
			time += deltaTime.asSeconds();

			sf::Color color = rectangleShape.getFillColor();
			if(time <= transitionTime / 2.0f)
				color.a = (int)(time * (1.0f / (transitionTime / 2.0f)) * 255.0f);
			else if(time <= transitionTime)
			{
				color.a = (int)((transitionTime - time) * (1.0f / (transitionTime / 2.0f)) * 255.0f);
				
				if(!updated)
				{
					Floor::player.sprite.setPosition(position);
					Floor::setCurrentRoom(playerPosX, playerPosY);
					hud.setCurrentRoom(playerPosX, playerPosY);
					updated = true;
				}
			}
			else
			{
				transitioning = false;
				time = 0.0f;
				updated = false;
			}

			rectangleShape.setFillColor(color);
		}
	}
}

void TransitionSystem::draw(sf::RenderWindow& window)
{
	if(transitioning)
		window.draw(rectangleShape);
}