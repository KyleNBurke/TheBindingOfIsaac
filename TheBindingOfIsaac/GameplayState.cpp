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
#include "PauseMenuState.hpp"
#include "HealthCom.hpp"

int GameplayState::playerBombs = 0;
int GameplayState::playerCoins = 0;

GameplayState::GameplayState(StatsState& statsState) :
	statsState(statsState),
	transitionSystem(GameManager::getInstance().getTimeStep(), hud),
	renderSystem(GameManager::getInstance().getWindow()),
	currentFloor(1)
{
	std::srand((int)std::time(0));
	floor.generate();
	hud.constructFloor(floor.getFloor());
	hud.setCurrentRoom(4, 2);

	const sf::Time& deltaTime = GameManager::getInstance().getTimeStep();

	systems.push_back(std::unique_ptr<System>(new InputSystem()));
	systems.push_back(std::unique_ptr<System>(new PhysicsSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new MovementSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new ShotSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new ProjectileSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new FlashSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new LifetimeSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new AnimationSystem(deltaTime)));
	systems.push_back(std::unique_ptr<System>(new ItemSystem(deltaTime)));

	reset();
	//updatePlayerCoins(100);
	HUD::showNewLevelMessage(currentFloor);
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
		statsState.setUpdatable(!statsState.getUpdatable());
		statsState.setDrawable(!statsState.getDrawable());

		if(statsState.getUpdatable())
			statsState.reset();
	}

	/*
	if(Input::getInstance().keyPressed(sf::Keyboard::Key::F))
		for(std::vector<Entity>::iterator& it = entities.begin(); it != entities.end(); ++it)
			if(it->hasComponent(Component::ComponentType::Health))
				Floor::getCurrentRoom().killEnemy(*it);

	if(Input::getInstance().keyPressed(sf::Keyboard::Key::G))
	{
		Floor::floorComplete = true;
		std::cout << "floor complete" << std::endl;
	}
	*/

	if(Input::getInstance().keyPressed(sf::Keyboard::Key::Escape))
	{
		GameManager::getInstance().addState(std::shared_ptr<PauseMenuState>(new PauseMenuState(*this)));
		setUpdatable(false);
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
				entityIt = entities.erase(entityIt);
			else
				++entityIt;
		}

		if(&Floor::getCurrentRoom() == &Floor::getRoom(Floor::sizeX / 2, Floor::sizeY / 2))
		{
			int tileScale = Utilities::getInstance().getScale() * Room::tileSize;
			int x = Room::width / 2 * tileScale;
			int y = Room::height / 2 * tileScale;

			if(Floor::floorComplete && Floor::player.getBounds().intersects(sf::FloatRect((float)x, (float)y, (float)tileScale, (float)tileScale)))
			{
				floor.generate();
				hud.constructFloor(floor.getFloor());
				Floor::floorComplete = false;
				HUD::showNewLevelMessage(++currentFloor);
			}
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

void GameplayState::reset()
{
	playerBombs = 3;
	HUD::updatePlayerBombs(playerBombs);

	playerCoins = 0;
	HUD::updatePlayerCoins(playerCoins);

	std::shared_ptr<HealthCom> healthCom = std::dynamic_pointer_cast<HealthCom>(Floor::player.getComponent(Component::ComponentType::Health));
	healthCom->health = 6;
	HUD::updatePlayerHealth(healthCom->health);

	Floor::resetPlayerComponents();
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

int GameplayState::getPlayerCoins()
{
	return playerCoins;
}

StatsState& GameplayState::getStatsState() const
{
	return statsState;
}