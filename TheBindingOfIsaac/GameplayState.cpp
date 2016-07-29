#include "stdafx.h"
#include "GameplayState.hpp"
#include "Input.hpp"
#include "GameManager.hpp"

GameplayState::GameplayState(StatsState& statsState, sf::RenderWindow& window, const sf::Time& deltaTime) :
	statsState(statsState),
	transitionSystem(deltaTime, hud),
	renderSystem(window)
{
	std::srand((int)std::time(0));
	floor.generate();
	hud.constructFloor(floor.getFloor());
	hud.setCurrentRoom(4, 2);

	systems.push_back(std::unique_ptr<System>(new InputSystem()));
	systems.push_back(std::unique_ptr<System>(new PhysicsSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new ShotSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new ProjectileSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new AnimationSystem(deltaTime)));
}

void GameplayState::initialize()
{
	Assemblages::getInstance().initialize();
}

void GameplayState::update(sf::Time deltaTime)
{
	for(std::vector<Entity>::iterator& it = Floor::getCurrentRoom().addEntityQueue.begin(); it != Floor::getCurrentRoom().addEntityQueue.end(); ++it)
		Floor::getCurrentRoom().entities.push_back(*it);
	Floor::getCurrentRoom().addEntityQueue.clear();

	if(Input::getInstance().keyPressed(sf::Keyboard::Key::Space))
	{
		std::srand((int)std::time(0) * std::rand());
		floor.generate();
	}

	if(Input::getInstance().keyPressed(sf::Keyboard::Key::F1)) {
		statsState.setActive(!statsState.getActive());

		if(statsState.getActive())
			statsState.reset();
	}

	if(!transitionSystem.transitioning)
		for(std::vector<std::unique_ptr<System>>::iterator it = systems.begin(); it != systems.end(); ++it)
			(*it)->update(Floor::player);

	transitionSystem.update(Floor::player);

	if(!transitionSystem.transitioning)
	{
		std::vector<Entity>::iterator entityIt = Floor::getCurrentRoom().entities.begin();
		while(entityIt != Floor::getCurrentRoom().entities.end())
		{
			for(std::vector<std::unique_ptr<System>>::iterator systemIt = systems.begin(); systemIt != systems.end(); ++systemIt)
				(*systemIt)->update(*entityIt);

			if(entityIt->shouldDelete)
				entityIt = Floor::getCurrentRoom().entities.erase(entityIt);
			else
				++entityIt;
		}
	}
}

void GameplayState::draw(sf::RenderWindow& window)
{
	floor.draw(window);

	renderSystem.update(Floor::player);
	for(std::vector<Entity>::iterator it = Floor::getCurrentRoom().entities.begin(); it != Floor::getCurrentRoom().entities.end(); ++it)
		renderSystem.update(*it);

	transitionSystem.draw(window);

	hud.draw(window);
}