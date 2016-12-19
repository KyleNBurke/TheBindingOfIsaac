#include "stdafx.h"
#include "GameplayState.hpp"
#include "Input.hpp"
#include "GameManager.hpp"
#include "Assemblages.hpp"
#include "InputSystem.hpp"
#include "PhysicsSystem.hpp"
#include "ShotSystem.hpp"
#include "ProjectileSystem.hpp"
#include "AnimationSystem.hpp"
#include "MovementSystem.hpp"
#include "FlashSystem.hpp"
#include "LifetimeSystem.hpp"
#include "ItemSystem.hpp"

int GameplayState::playerBombs = 0;
int GameplayState::playerCoins = 0;

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
	systems.push_back(std::unique_ptr<System>(new MovementSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new ShotSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new ProjectileSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new FlashSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new LifetimeSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new AnimationSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new ItemSystem(deltaTime)));

	updatePlayerBombs(10);
}

void GameplayState::initialize()
{
	Assemblages::getInstance().initialize();
}

void GameplayState::update(sf::Time deltaTime)
{
	std::vector<Entity>& queue = Floor::getCurrentRoom().getAddEntityQueue();
	std::vector<Entity>& entities = Floor::getCurrentRoom().getEntities();

	for(std::vector<Entity>::iterator& itToAdd = queue.begin(); itToAdd != queue.end(); ++itToAdd)
	{
		bool added = false;

		for(std::vector<Entity>::iterator& it = entities.begin(); it != entities.end(); ++it)
		{
			if(itToAdd->drawPriority < it->drawPriority)
			{
				entities.insert(it, *itToAdd);
				added = true;
				break;
			}
		}

		if(!added)
			entities.push_back(*itToAdd);
	}
	queue.clear();

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
		std::vector<Entity>::iterator entityIt = entities.begin();
		while(entityIt != entities.end())
		{
			for(std::vector<std::unique_ptr<System>>::iterator systemIt = systems.begin(); systemIt != systems.end(); ++systemIt)
				(*systemIt)->update(*entityIt);

			if(entityIt->shouldDelete)
				entityIt = Floor::getCurrentRoom().removeEntity(entityIt);
			else
				++entityIt;
		}

		hud.update();
	}
}

void GameplayState::draw(sf::RenderWindow& window)
{
	Room& room = Floor::getCurrentRoom();

	room.drawBackground(window);

	for(std::vector<Entity>::iterator it = room.getEntities().begin(); it != room.getEntities().end(); ++it)
		renderSystem.update(*it);

	renderSystem.update(Floor::player);

	room.drawForeground(window);

	transitionSystem.draw(window);

	hud.draw(window);
}

void GameplayState::updatePlayerBombs(int amount)
{
	playerBombs += amount;
	HUD::updatePlayerBombs(playerBombs);
}

int GameplayState::getPlayerBombs()
{
	return playerBombs;
}

void GameplayState::updatePlayerCoins(int amount)
{
	playerCoins += amount;
	HUD::updatePlayerCoins(playerCoins);
}