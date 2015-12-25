#pragma once

#include "stdafx.h"
#include "State.hpp"

class StatsState : public State {
public:
	StatsState();

	void initialize();

	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

	void reset();

private:
	sf::Text fps;
	sf::Text drawCalls;

	sf::Clock clockUpdate;
	sf::Clock clockDraw;
	int frames;
	int draws;
};