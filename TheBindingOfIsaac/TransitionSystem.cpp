#include "stdafx.h"
#include "TransitionSystem.hpp"
#include "Utilities.hpp"
#include "GameManager.hpp"

TransitionSystem::TransitionSystem(const sf::Time& deltaTime) : deltaTime(deltaTime), transitioning(false), time(0.0f), transitionTime(0.3f)
{
	int scale = Utilities::getInstance().getScale() * Room::tileSize;
	rectangleShape.setSize(sf::Vector2f((float)(Room::width * scale), (float)(Room::height * scale)));
	rectangleShape.setFillColor(sf::Color::Black);
}

void TransitionSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::PlayerControlled))
	{
		sf::FloatRect bounds = entity.sprite.getGlobalBounds();
		int scale = Utilities::getInstance().getScale() * Room::tileSize;

		if(bounds.top < 0.0f)
		{
			transitioning = true;
			direction = Floor::Direction::Up;
		}
		else if(bounds.top + bounds.height > Room::height * scale)
		{
			transitioning = true;
			direction = Floor::Direction::Down;
		}
		else if(bounds.left < 0.0f)
		{
			transitioning = true;
			direction = Floor::Direction::Left;
		}
		else if(bounds.left + bounds.width > Room::width * scale)
		{
			transitioning = true;
			direction = Floor::Direction::Right;
		}

		if(transitioning)
		{
			float prevTime = time;
			time += deltaTime.asSeconds();

			sf::Color color = rectangleShape.getFillColor();
			if(time <= transitionTime / 2.0f)
				color.a = (int)(time * (1.0f / (transitionTime / 2.0f)) * 255.0f);
			else if(time <= transitionTime)
				color.a = (int)((transitionTime - time) * (1.0f / (transitionTime / 2.0f)) * 255.0f);
			else
			{
				transitioning = false;
				time = 0.0f;
			}

			if(prevTime <= transitionTime / 2.0f && time >= transitionTime / 2.0f)
				Floor::transitionRoom(direction);

			rectangleShape.setFillColor(color);
		}
	}
}

void TransitionSystem::draw(sf::RenderWindow& window)
{
	if(transitioning)
		window.draw(rectangleShape);
}