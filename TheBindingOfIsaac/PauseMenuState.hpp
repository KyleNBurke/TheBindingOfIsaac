#pragma once

#include "stdafx.h"
#include "State.hpp"
#include "GameplayState.hpp"

class PauseMenuState : public State
{
public:
	PauseMenuState(GameplayState& gameplayState);

	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape background;
	sf::Text continueText;
	sf::Text exitText;
	sf::Texture arrowSprite;
	sf::Sprite arrow;
	bool continueSelected;
	GameplayState& gameplayState;
};