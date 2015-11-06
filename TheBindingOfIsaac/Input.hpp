#pragma once

#include "stdafx.h"

class Input
{
public:
	static Input& getInstance();

	friend class GameManager;

	bool keyPressed(sf::Keyboard::Key key);
	bool keyReleased(sf::Keyboard::Key key);
	bool keyHeld(sf::Keyboard::Key key);
	bool mouseButtonPressed(sf::Mouse::Button button);
	bool mouseButtonReleased(sf::Mouse::Button button);
	bool mouseButtonHeld(sf::Mouse::Button button);
	int getMouseWheelTicks() const;

private:
	Input();
	Input(const Input&);
	void operator=(const Input&);

	void clearInput();

	std::vector<sf::Keyboard::Key> pressedKeys;
	std::vector<sf::Keyboard::Key> releasedKeys;
	std::vector<sf::Mouse::Button> pressedMouseButtons;
	std::vector<sf::Mouse::Button> releasedMouseButtons;
	int mouseWheelTicks;
};