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
	bool getUpdatable() const;
	void setUpdatable(bool updatable);
	bool getDrawable() const;
	void setDrawable(bool drawable);

protected:
	bool deleteState;
	bool updatable;
	bool drawable;
};