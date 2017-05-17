#pragma once

#include "stdafx.h"
#include "State.hpp"

class MainMenuState : public State
{
public:
	MainMenuState();

	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

private:
	sf::Text playText;
	sf::Text exitText;
	sf::Texture arrowSprite;
	sf::Sprite arrow;
	bool playSelected;
};