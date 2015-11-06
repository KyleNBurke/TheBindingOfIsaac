#include "stdafx.h"
#include "GameplayState.hpp"
#include "Input.hpp"

GameplayState::GameplayState(sf::RenderWindow& window, const sf::Time& deltaTime) : map(hud), renderSystem(window), inputSystem(), physicsSystem(deltaTime)
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