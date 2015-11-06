#include "stdafx.h"
#include "Input.hpp"

Input::Input() : mouseWheelTicks(0) {}

Input& Input::getInstance()
{
	static Input instance;
	return instance;
}

void Input::clearInput()
{
	pressedKeys.clear();
	releasedKeys.clear();
	pressedMouseButtons.clear();
	releasedMouseButtons.clear();
	mouseWheelTicks = 0;
}

bool Input::keyPressed(sf::Keyboard::Key key)
{
	for (std::vector<sf::Keyboard::Key>::iterator it = pressedKeys.begin(); it != pressedKeys.end(); ++it)
		if (*it == key)
			return true;

	return false;
}

bool Input::keyReleased(sf::Keyboard::Key key)
{
	for (std::vector<sf::Keyboard::Key>::iterator it = releasedKeys.begin(); it != releasedKeys.end(); ++it)
		if (*it == key)
			return true;

	return false;
}

bool Input::keyHeld(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}

bool Input::mouseButtonPressed(sf::Mouse::Button button)
{
	for (std::vector<sf::Mouse::Button>::iterator it = pressedMouseButtons.begin(); it != pressedMouseButtons.end(); ++it)
		if (*it == button)
			return true;

	return false;
}

bool Input::mouseButtonReleased(sf::Mouse::Button button)
{
	for (std::vector<sf::Mouse::Button>::iterator it = releasedMouseButtons.begin(); it != releasedMouseButtons.end(); ++it)
		if (*it == button)
			return true;

	return false;
}

bool Input::mouseButtonHeld(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button);
}

int Input::getMouseWheelTicks() const
{
	return mouseWheelTicks;
}