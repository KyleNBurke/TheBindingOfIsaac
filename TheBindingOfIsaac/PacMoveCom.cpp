#include "stdafx.h"
#include "PacMoveCom.hpp"

const float PacMoveCom::passiveSpeed = 150.0f;
const float PacMoveCom::aggressiveSpeed = 400.0f;
const float PacMoveCom::randInterval = 3.0f;
const float PacMoveCom::randOffset = 1.0f;

PacMoveCom::PacMoveCom(Direction forwardsDir) :
	state(Passive),
	forwardsDir(forwardsDir),
	collided(false),
	elapsedTime(0.0f),
	travelTime((float)std::rand() / RAND_MAX * randInterval + randOffset)
{
	switch(forwardsDir)
	{
		case Up:
			backwardsDir = Down;
			break;
		case Down:
			backwardsDir = Up;
			break;
		case Left:
			backwardsDir = Right;
			break;
		case Right:
			backwardsDir = Left;
			break;
	}
}

Component::ComponentType PacMoveCom::getType() const
{
	return ComponentType::PacMove;
}