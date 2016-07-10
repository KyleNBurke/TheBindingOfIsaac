#pragma once

#include "stdafx.h"
#include "System.hpp"
#include "Floor.hpp"

class TransitionSystem : public System
{
public:
	TransitionSystem(const sf::Time& deltaTime);

	void update(Entity& entity);
	void draw(sf::RenderWindow& window);

	bool transitioning;
	sf::RectangleShape rectangleShape;

private:
	const sf::Time& deltaTime;
	float time;
	const float transitionTime;
	Floor::Direction direction;
};