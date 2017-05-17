#include "stdafx.h"
#include "MainMenuState.hpp"
#include "Utilities.hpp"
#include "GameManager.hpp"
#include "Input.hpp"
#include "StatsState.hpp"
#include "GameplayState.hpp"

MainMenuState::MainMenuState() :
	playSelected(true)
{
	sf::Vector2u windowSize = GameManager::getInstance().getWindow().getSize();
	int scale = Utilities::getInstance().getScale();

	playText.setFont(Utilities::getInstance().getFont());
	playText.setCharacterSize(scale * 8);
	playText.setString("Start");
	playText.setPosition(windowSize.x / 2.0f - playText.getGlobalBounds().width / 2.0f, windowSize.y / 2.0f - 25.0f * scale);

	exitText.setFont(Utilities::getInstance().getFont());
	exitText.setCharacterSize(scale * 8);
	exitText.setString("Exit");
	exitText.setPosition(windowSize.x / 2.0f - exitText.getGlobalBounds().width / 2.0f, windowSize.y / 2.0f - 10.0f * scale);

	arrowSprite.loadFromFile("Resources/menuArrow.png");

	arrow.setTexture(arrowSprite);
	arrow.setScale((float)scale, (float)scale);
	arrow.setPosition(windowSize.x / 2.0f - 22.0f * scale, playText.getGlobalBounds().top + playText.getGlobalBounds().height / 2.0f - arrow.getGlobalBounds().height / 2.0f);
}

void MainMenuState::update(sf::Time deltaTime)
{
	if(Input::getInstance().keyPressed(sf::Keyboard::Key::Up) || Input::getInstance().keyPressed(sf::Keyboard::Key::Down))
	{
		playSelected = !playSelected;

		if(playSelected)
		{
			sf::Vector2f position = arrow.getPosition();
			position.y = playText.getGlobalBounds().top + playText.getGlobalBounds().height / 2.0f - arrow.getGlobalBounds().height / 2.0f;
			arrow.setPosition(position);
		}
		else
		{
			sf::Vector2f position = arrow.getPosition();
			position.y = exitText.getGlobalBounds().top + exitText.getGlobalBounds().height / 2.0f - arrow.getGlobalBounds().height / 2.0f;
			arrow.setPosition(position);
		}
	}

	if(Input::getInstance().keyPressed(sf::Keyboard::Key::Return))
	{
		if(playSelected)
		{
			std::shared_ptr<StatsState> statsState(new StatsState());
			std::shared_ptr<GameplayState> gameplayState(new GameplayState(*statsState));
			GameManager::getInstance().addState(gameplayState);
			gameplayState->initialize();
			GameManager::getInstance().addState(statsState);
			statsState->initialize();
			deleteState = true;
		}
		else
			GameManager::getInstance().getWindow().close();
	}
}

void MainMenuState::draw(sf::RenderWindow& window)
{
	window.draw(playText);
	window.draw(exitText);
	window.draw(arrow);
}