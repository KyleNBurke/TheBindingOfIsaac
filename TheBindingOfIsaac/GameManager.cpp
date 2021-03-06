#include "stdafx.h"
#include "GameManager.hpp"
#include "Input.hpp"
#include "GameplayState.hpp"
#include "StatsState.hpp"
#include "Utilities.hpp"
#include "Room.hpp"

#include "MainMenuState.hpp"

GameManager::GameManager() : windowHasFocus(true),
timeStep(sf::seconds(1.0f / 60.0f)) {}

GameManager& GameManager::getInstance()
{
	static GameManager instance;
	return instance;
}

void GameManager::initialize()
{
	Utilities::getInstance().initialize();

	int scale = Utilities::getInstance().getScale();
	int tileSize = Room::tileSize;

	sf::Vector2i windowSize = sf::Vector2i(tileSize * scale * Room::width, tileSize * scale * Room::height + (22 * scale));

	window.create(sf::VideoMode(windowSize.x, windowSize.y), "The Binding of Isaac");
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
	std::shared_ptr<StatsState> statsState(new StatsState());
	//std::shared_ptr<GameplayState> gameplayState(new GameplayState(*statsState));
	//addState(gameplayState);
	//gameplayState->initialize();
	addState(statsState);
	statsState->initialize();

	std::shared_ptr<MainMenuState> mainMenuState(new MainMenuState());
	addState(mainMenuState);
}

void GameManager::gameLoop()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::LostFocus:
				windowHasFocus = false;
				break;
			case sf::Event::GainedFocus:
				windowHasFocus = true;
				break;
			case sf::Event::KeyPressed:
				Input::getInstance().pressedKeys.push_back(event.key.code);
				break;
			case sf::Event::KeyReleased:
				Input::getInstance().releasedKeys.push_back(event.key.code);
				break;
			case sf::Event::MouseButtonPressed:
				Input::getInstance().pressedMouseButtons.push_back(event.mouseButton.button);
				break;
			case sf::Event::MouseButtonReleased:
				Input::getInstance().releasedMouseButtons.push_back(event.mouseButton.button);
				break;
			case sf::Event::MouseWheelMoved:
				Input::getInstance().mouseWheelTicks = event.mouseWheel.delta;
				break;
			default:
				break;
			}
		}

		elapsedTime += clock.restart();

		if(elapsedTime >= timeStep)
		{
			for (std::vector<std::shared_ptr<State>>::iterator it = statesToAdd.begin(); it != statesToAdd.end(); ++it)
				states.push_back(std::move(*it));

			if (!statesToAdd.empty())
				statesToAdd.clear();

			while(elapsedTime >= timeStep)
			{
				elapsedTime -= timeStep;

				for (std::vector<std::shared_ptr<State>>::iterator it = states.begin(); it != states.end();)
				{
					if ((*it)->getUpdatable())
						(*it)->update(timeStep);

					if ((*it)->getDeleteState())
						it = states.erase(it);
					else
						++it;
				}
			}

			window.clear();

			for (std::vector<std::shared_ptr<State>>::iterator it = states.begin(); it != states.end(); ++it)
			{
				if((*it)->getDrawable())
					(*it)->draw(window);
			}

			window.display();

			Input::getInstance().clearInput();
		}
	}
}

void GameManager::addState(std::shared_ptr<State> state)
{
	statesToAdd.push_back(std::move(state));
}

void GameManager::resetGameplay()
{
	for(std::vector<std::shared_ptr<State>>::iterator it = states.begin(); it != states.end(); ++it)
		(*it)->setDeleteState(true);

	std::shared_ptr<StatsState> statsState(new StatsState());
	std::shared_ptr<GameplayState> gameplayState(new GameplayState(*statsState));
	addState(gameplayState);
	gameplayState->initialize();
	addState(statsState);
	statsState->initialize();
}

sf::RenderWindow& GameManager::getWindow()
{
	return window;
}

bool GameManager::getWindowHasFocus() const
{
	return windowHasFocus;
}

const sf::Time& GameManager::getTimeStep() const
{
	return timeStep;
}