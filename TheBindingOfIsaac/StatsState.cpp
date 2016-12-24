#include "stdafx.h"
#include "StatsState.hpp"
#include "Utilities.hpp"

StatsState::StatsState() : fps("FPS: -", Utilities::getInstance().getFont()), drawCalls("Draw Calls: ", Utilities::getInstance().getFont()), frames(0), draws(0)
{
	active = false;
}

void StatsState::initialize() {
	fps.setPosition(10.0f, 5.0f);
	drawCalls.setPosition(10.0f, 35.0f);
}

void StatsState::update(sf::Time deltaTime) {
	if(clockUpdate.getElapsedTime().asSeconds() >= 1.0f) {
		fps.setString("FPS: " + std::to_string(frames));
		frames = 0;
		clockUpdate.restart();
	}

	frames++;
}

void StatsState::draw(sf::RenderWindow& window) {
	if(clockDraw.getElapsedTime().asSeconds() >= 1.0f) {
		drawCalls.setString("Draw Calls: " + std::to_string(draws));
		draws = 0;
		clockDraw.restart();
	}

	draws++;

	window.draw(fps);
	window.draw(drawCalls);
}

void StatsState::reset() {
	frames = 0;
	draws = 0;
	fps.setString("FPS: -");
	drawCalls.setString("Draw Calls: -");
	clockUpdate.restart();
	clockDraw.restart();
}