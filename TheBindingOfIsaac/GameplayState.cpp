#include "stdafx.h"
#include "GameplayState.hpp"
#include "Input.hpp"

GameplayState::GameplayState(StatsState& statsState, sf::RenderWindow& window, const sf::Time& deltaTime) :
	statsState(statsState),
	map(hud),
	renderSystem(window)
{
	Room::initialize();
	map.generate(std::rand());

	systems.push_back(std::unique_ptr<System>(new InputSystem()));
	systems.push_back(std::unique_ptr<System>(new PhysicsSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new ShotSystem()));
	systems.push_back(std::unique_ptr<System>(new ProjectileSystem(deltaTime)));
}

void GameplayState::initialize()
{
	Assemblages::getInstance().initialize();
}

void GameplayState::update(sf::Time deltaTime)
{
	for(std::vector<Entity>::iterator& it = Map::getCurrentRoom().addEntityQueue.begin(); it != Map::getCurrentRoom().addEntityQueue.end(); ++it)
		Map::getCurrentRoom().entities.push_back(*it);
	Map::getCurrentRoom().addEntityQueue.clear();

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

	for(std::vector<std::unique_ptr<System>>::iterator it = systems.begin(); it != systems.end(); ++it)
		(*it)->update(Map::player);

	std::vector<Entity>::iterator entityIt = Map::getCurrentRoom().entities.begin();
	while(entityIt != Map::getCurrentRoom().entities.end())
	{
		for(std::vector<std::unique_ptr<System>>::iterator systemIt = systems.begin(); systemIt != systems.end(); ++systemIt)
			(*systemIt)->update(*entityIt);

		if (entityIt->shouldDelete)
			entityIt = Map::getCurrentRoom().entities.erase(entityIt);
		else
			++entityIt;
	}
}

void GameplayState::draw(sf::RenderWindow& window)
{
	map.draw(window);
	hud.draw(window);

	renderSystem.update(Map::player);
	for(std::vector<Entity>::iterator it = Map::getCurrentRoom().entities.begin(); it != Map::getCurrentRoom().entities.end(); ++it)
		renderSystem.update(*it);
}