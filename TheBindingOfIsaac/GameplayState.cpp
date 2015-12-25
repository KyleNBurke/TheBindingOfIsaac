#include "stdafx.h"
#include "GameplayState.hpp"
#include "Input.hpp"

GameplayState::GameplayState(StatsState& statsState, sf::RenderWindow& window, const sf::Time& deltaTime) : statsState(statsState), map(hud), renderSystem(window), inputSystem(), collisionSystem(deltaTime)
{
	Room::initialize();

	map.generate(std::rand());
}

void GameplayState::initialize()
{
	//each room will hold the entities but for now just use this class
	entities.push_back(Assemblages::getInstance().createPlayer());
}

void GameplayState::update(sf::Time deltaTime)
{
	//player.update(deltaTime);

	if(Input::getInstance().keyPressed(sf::Keyboard::Key::Space))
	{
		std::srand((int)std::time(0) * std::rand());
		map.generate(std::rand());
	}

	if(Input::getInstance().keyPressed(sf::Keyboard::Key::F1)) {
		statsState.setActive(!statsState.getActive());

		if(statsState.getActive()) {
			statsState.reset();
		}
	}

	//-----------------------------------------------------------------------------
	inputSystem.update(entities);
	physicsSystem.update(entities);
	collisionSystem.update(entities);

}

void GameplayState::draw(sf::RenderWindow& window)
{
	map.draw(window);
	//player.draw(window);
	hud.draw(window);

	//-----------------------------------------------------------------------------

	renderSystem.update(entities);
}