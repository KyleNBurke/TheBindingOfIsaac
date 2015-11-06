#include "stdafx.h"
#include "State.hpp"

State::State() : deleteState(false), active(true) {}

void State::update(sf::Time deltaTime) {}

void State::draw(sf::RenderWindow& window) {}

void State::setDeleteState(bool deleteState)
{
	this->deleteState = deleteState;
}

bool State::getDeleteState() const
{
	return deleteState;
}

void State::setActive(bool active)
{
	this->active = active;
}

bool State::getActive() const
{
	return active;
}