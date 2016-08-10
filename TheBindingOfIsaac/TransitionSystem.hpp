#pragma once

#include "stdafx.h"
#include "System.hpp"
#include "HUD.hpp"

class TransitionSystem : public System
{
public:
	TransitionSystem(const sf::Time& deltaTime, HUD& hud);

	void update(Entity& entity);
	void draw(sf::RenderWindow& window);

	bool transitioning;
	sf::RectangleShape rectangleShape;

private:
	const sf::Time& deltaTime;
	float time;
	const float transitionTime;
	bool updated;
	sf::Vector2f position;
	int playerPosX;
	int playerPosY;
	HUD& hud;
};