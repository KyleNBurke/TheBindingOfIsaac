#include "stdafx.h"
#include "GameplayState.hpp"
#include "Input.hpp"

GameplayState::GameplayState(StatsState& statsState, sf::RenderWindow& window, const sf::Time& deltaTime) : 
	statsState(statsState),
	map(hud),
	renderSystem(window),
	physicsSystem(deltaTime),
	projectileSystem(deltaTime)
{
	Room::initialize();

	map.generate(std::rand());
}

void GameplayState::initialize()
{
	Assemblages::getInstance().initialize();
}

void GameplayState::update(sf::Time deltaTime)
{
	for(std::vector<Entity>::iterator& it = Room::addEntityQueue.begin(); it != Room::addEntityQueue.end(); ++it)
		Room::entities.push_back(*it);
	Room::addEntityQueue.clear();

	if(Input::getInstance().keyPressed(sf::Keyboard::Key::Space))
	{
		std::srand((int)std::time(0) * std::rand());
		map.generate(std::rand());
	}

	if(Input::getInstance().keyPressed(sf::Keyboard::Key::F1)) {
		statsState.setActive(!statsState.getActive());

		if(statsState.getActive())
			statsState.reset();
	}

	std::vector<Entity>::iterator it = Room::entities.begin();
	while(it != Room::entities.end())
	{
		inputSystem.update(*it);
		physicsSystem.update(*it);
		projectileSystem.update(*it);

		if (it->shouldDelete)
			it = Room::entities.erase(it);
		else
			++it;
	}
}

void GameplayState::draw(sf::RenderWindow& window)
{
	map.draw(window);
	hud.draw(window);

	for(std::vector<Entity>::iterator it = Room::entities.begin(); it != Room::entities.end(); ++it)
	{
		renderSystem.update(*it);
	}
}