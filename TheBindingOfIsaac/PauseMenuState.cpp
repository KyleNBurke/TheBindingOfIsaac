#include "stdafx.h"
#include "PauseMenuState.hpp"
#include "Utilities.hpp"
#include "GameManager.hpp"
#include "Room.hpp"
#include "Input.hpp"
#include "MainMenuState.hpp"

PauseMenuState::PauseMenuState(GameplayState& gameplayState) : gameplayState(gameplayState)
{
	int scale = Utilities::getInstance().getScale();

	background.setPosition(scale * Room::tileSize * 2.0f, scale * Room::tileSize * 3.0f);
	background.setSize(sf::Vector2f(scale * Room::tileSize * 13.0f, scale * Room::tileSize * 6.0f));
	background.setFillColor(sf::Color(50, 50, 50));

	sf::Vector2u windowSize = GameManager::getInstance().getWindow().getSize();

	continueText.setFont(Utilities::getInstance().getFont());
	continueText.setCharacterSize(scale * 8);
	continueText.setString("Continue");
	continueText.setPosition(windowSize.x / 2.0f - continueText.getGlobalBounds().width / 2.0f, windowSize.y / 2.0f - 25.0f * scale);

	exitText.setFont(Utilities::getInstance().getFont());
	exitText.setCharacterSize(scale * 8);
	exitText.setString("Exit");
	exitText.setPosition(windowSize.x / 2.0f - exitText.getGlobalBounds().width / 2.0f, windowSize.y / 2.0f - 10.0f * scale);

	arrowSprite.loadFromFile("Resources/menuArrow.png");

	arrow.setTexture(arrowSprite);
	arrow.setScale((float)scale, (float)scale);
	arrow.setPosition(windowSize.x / 2.0f - 26.0f * scale, continueText.getGlobalBounds().top + continueText.getGlobalBounds().height / 2.0f - arrow.getGlobalBounds().height / 2.0f);
}

void PauseMenuState::update(sf::Time deltaTime)
{
	if(Input::getInstance().keyPressed(sf::Keyboard::Key::Up) || Input::getInstance().keyPressed(sf::Keyboard::Key::Down))
	{
		continueSelected = !continueSelected;

		if(continueSelected)
		{
			sf::Vector2f position = arrow.getPosition();
			position.y = continueText.getGlobalBounds().top + continueText.getGlobalBounds().height / 2.0f - arrow.getGlobalBounds().height / 2.0f;
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
		if(continueSelected)
		{
			setDeleteState(true);
			gameplayState.setUpdatable(true);
		}
		else
		{
			gameplayState.setDeleteState(true);
			gameplayState.getStatsState().setDeleteState(true);
			setDeleteState(true);

			GameManager::getInstance().addState(std::shared_ptr<MainMenuState>(new MainMenuState()));
		}
	}
}

void PauseMenuState::draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(continueText);
	window.draw(exitText);
	window.draw(arrow);
}