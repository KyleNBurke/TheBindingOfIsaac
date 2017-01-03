#include "stdafx.h"
#include "WalkMoveCom.hpp"

WalkMoveCom::WalkMoveCom(Direction forwardDir, float speed) :
	speed(speed),
	collided(false),
	elapsedTime(0.0f),
	travelTime(4.0f),
	randInterval(3.0f),
	randOffset(1.0f),
	forwardDir(forwardDir),
	backwardDir(setBackwardDir())
{}

Component::ComponentType WalkMoveCom::getType() const
{
	return Component::ComponentType::WalkMove;
}

Direction WalkMoveCom::setBackwardDir()
{
	switch(forwardDir)
	{
		case Direction::Up:
			return Direction::Down;
		case Direction::Down:
			return Direction::Up;
		case Direction::Left:
			return Direction::Right;
		case Direction::Right:
			return Direction::Left;
		default:
			return Direction::Up;
	}
}