#pragma once

#include "stdafx.h"

class State
{
public:
	State();

	virtual void update(sf::Time deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	void setDeleteState(bool deleteState);
	bool getDeleteState() const;
	void setActive(bool active);
	bool getActive() const;

protected:
	bool deleteState;
	bool active;
};