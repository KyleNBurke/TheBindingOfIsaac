#include "stdafx.h"
#include "State.hpp"

State::State() : deleteState(false), updatable(true), drawable(true) {}

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

void State::setUpdatable(bool updatable)
{
	this->updatable = updatable;
}

bool State::getUpdatable() const
{
	return updatable;
}

void State::setDrawable(bool drawable)
{
	this->drawable = drawable;
}

bool State::getDrawable() const
{
	return drawable;
}