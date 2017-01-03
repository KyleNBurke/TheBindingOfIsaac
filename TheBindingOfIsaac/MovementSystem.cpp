#include "stdafx.h"
#include "MovementSystem.hpp"
#include "PacMoveCom.hpp"
#include "Floor.hpp"
#include "VelocityCom.hpp"
#include "AnimationCom.hpp"
#include "JimmyMoveCom.hpp"
#include "AccelerationCom.hpp"
#include "FlyMoveCom.hpp"
#include "DashieMoveCom.hpp"
#include "WalkMoveCom.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

MovementSystem::MovementSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void MovementSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::PacMove))
	{
		std::shared_ptr<PacMoveCom> moveCom = std::dynamic_pointer_cast<PacMoveCom>(entity.getComponent(Component::ComponentType::PacMove));
		std::shared_ptr<AnimationCom> animCom = std::dynamic_pointer_cast<AnimationCom>(entity.getComponent(Component::ComponentType::Animation));

		switch(moveCom->state)
		{
			case PacMoveCom::State::Passive:
				if(searchForPlayer(entity))
				{
					moveCom->state = PacMoveCom::State::Aggressive;
					animCom->currentState = 1;
				}
				else
				{
					moveCom->elapsedTime += deltaTime.asSeconds();

					if(moveCom->collided || moveCom->elapsedTime > moveCom->travelTime)
					{
						calculatePacTurn(entity);

						moveCom->collided = false;
						moveCom->travelTime = (float)std::rand() / RAND_MAX * moveCom->randInterval + moveCom->randOffset;
						moveCom->elapsedTime = 0.0f;
					}

					break;
				}
			case PacMoveCom::State::Aggressive:
				if(moveCom->collided)
				{
					moveCom->state = PacMoveCom::State::Passive;
					calculatePacTurn(entity);
					moveCom->collided = false;
					animCom->currentState = 0;
				}
				break;
		}
	}
	else if(entity.hasComponent(Component::ComponentType::JimmyMove))
	{
		std::shared_ptr<JimmyMoveCom> moveCom = std::dynamic_pointer_cast<JimmyMoveCom>(entity.getComponent(Component::ComponentType::JimmyMove));
		std::shared_ptr<VelocityCom> velCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));
		std::shared_ptr<AccelerationCom> accelCom = std::dynamic_pointer_cast<AccelerationCom>(entity.getComponent(Component::ComponentType::AccelDecel));

		sf::Vector2f direction = moveCom->centerPosition - entity.position;

		float directionRad = std::atan(direction.y / direction.x);
		if(direction.x < 0.0f)
			directionRad += (float)M_PI;

		float randomRadAmount = 2.0f;
		directionRad += (float)std::rand() / (float)RAND_MAX * randomRadAmount - randomRadAmount / 2;

		float newDirX = std::cos(directionRad);
		float newDirY = std::sin(directionRad);

		accelCom->acceleration = sf::Vector2f(newDirX, newDirY) * moveCom->accelerationSpeed;
	}
	else if(entity.hasComponent(Component::ComponentType::FlyMove))
	{
		std::shared_ptr<FlyMoveCom> moveCom = std::dynamic_pointer_cast<FlyMoveCom>(entity.getComponent(Component::ComponentType::FlyMove));
		std::shared_ptr<VelocityCom> velCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));

		sf::Vector2f direction = (Floor::player.position - entity.position);
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= length;

		velCom->velocity = direction * moveCom->speed;
	}
	else if(entity.hasComponent(Component::ComponentType::DashieMove))
	{
		std::shared_ptr<DashieMoveCom> moveCom = std::dynamic_pointer_cast<DashieMoveCom>(entity.getComponent(Component::ComponentType::DashieMove));
		std::shared_ptr<VelocityCom> velCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));
		std::shared_ptr<AccelerationCom> accelCom = std::dynamic_pointer_cast<AccelerationCom>(entity.getComponent(Component::ComponentType::AccelDecel));

		moveCom->currentMoveTime += deltaTime.asSeconds();

		if(moveCom->currentMoveTime >= moveCom->maxMoveTime)
		{
			moveCom->currentMoveTime = 0.0f;
			moveCom->maxMoveTime = (float)std::rand() / RAND_MAX * moveCom->randomMoveTimeAmount + moveCom->baseMoveTimeAmount;

			sf::Vector2f direction;
			if(moveCom->variation == DashieMoveCom::Variation::Random)
			{
				float directionRad = moveCom->prevDirectionRad + (float)M_PI / 4.0f + (float)std::rand() / RAND_MAX * (float)M_PI;

				directionRad = std::fmodf(directionRad, 2.0f * (float)M_PI);
				moveCom->prevDirectionRad = directionRad;
				direction = sf::Vector2f(std::cos(directionRad), std::sin(directionRad));
			}
			else
			{
				direction = (Floor::player.position - entity.position);
				float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
				direction /= length;
			}

			velCom->velocity = direction * moveCom->speed;
		}

		float length = std::sqrt(velCom->velocity.x * velCom->velocity.x + velCom->velocity.y * velCom->velocity.y);
		if(length == 0.0f)
			length = 1.0f;

		accelCom->acceleration = -velCom->velocity / length * moveCom->decel;
	}
	else if(entity.hasComponent(Component::ComponentType::WalkMove))
	{
		std::shared_ptr<WalkMoveCom> moveCom = std::dynamic_pointer_cast<WalkMoveCom>(entity.getComponent(Component::ComponentType::WalkMove));

		moveCom->elapsedTime += deltaTime.asSeconds();

		if(moveCom->collided || moveCom->elapsedTime > moveCom->travelTime)
		{
			calculateWalkTurn(entity);

			moveCom->collided = false;
			moveCom->travelTime = (float)std::rand() / RAND_MAX * moveCom->randInterval + moveCom->randOffset;
			moveCom->elapsedTime = 0.0f;
		}
	}
}

bool MovementSystem::searchForPlayer(Entity& entity)
{
	std::shared_ptr<PacMoveCom> moveCom = std::dynamic_pointer_cast<PacMoveCom>(entity.getComponent(Component::ComponentType::PacMove));
	std::shared_ptr<VelocityCom> velCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));

	int scale = Room::tileSize * Utilities::getInstance().getScale();
	float rotation = entity.sprite.getRotation();
	const int searchDist = 4;

	for(int d = 0; d < 4; d++)
	{
		sf::FloatRect searchArea;

		switch(d)
		{
			case Up:
			{
				entity.sprite.setRotation(-90.0f);
				sf::FloatRect bounds = entity.getBounds();
				int left = (int)(std::floorf(bounds.left / scale));
				int right = (int)(std::ceilf((bounds.left + bounds.width) / scale)) - 1;
				int top = (int)(std::floorf(bounds.top / scale));
				int bottom = (int)(std::ceilf((bounds.top + bounds.height) / scale)) - 1;

				int end = 0;
				for(int x = left; x <= right; x++)
				{
					int y = top;
					while(Floor::getCurrentRoom().getTileType(x, y) == Room::TileType::floor && y > top - searchDist)
						y--;

					end = std::max(end, y);
				}

				searchArea = sf::FloatRect(bounds.left, (float)(end + 1) * scale, bounds.width, bounds.top - (end + 1) * scale);

				if(Floor::player.getBounds().intersects(searchArea))
				{
					velCom->velocity = sf::Vector2f(0.0f, -moveCom->aggressiveSpeed);
					entity.sprite.setRotation(-90.0f);
					moveCom->forwardsDir = Up;
					moveCom->backwardsDir = Down;
					return true;
				}

				break;
			}
			case Down:
			{
				entity.sprite.setRotation(90.0f);
				sf::FloatRect bounds = entity.getBounds();
				int left = (int)(std::floorf(bounds.left / scale));
				int right = (int)(std::ceilf((bounds.left + bounds.width) / scale)) - 1;
				int top = (int)(std::floorf(bounds.top / scale));
				int bottom = (int)(std::ceilf((bounds.top + bounds.height) / scale)) - 1;

				int end = INT_MAX;
				for(int x = left; x <= right; x++)
				{
					int y = bottom;
					while(Floor::getCurrentRoom().getTileType(x, y) == Room::TileType::floor && y < bottom + searchDist)
						y++;

					end = std::min(end, y);
				}

				searchArea = sf::FloatRect(bounds.left, bounds.top + bounds.height, bounds.width, end * scale - (bounds.top + bounds.height));

				if(Floor::player.getBounds().intersects(searchArea))
				{
					velCom->velocity = sf::Vector2f(0.0f, moveCom->aggressiveSpeed);
					entity.sprite.setRotation(90.0f);
					moveCom->forwardsDir = Down;
					moveCom->backwardsDir = Up;
					return true;
				}

				break;
			}
			case Left:
			{
				entity.sprite.setRotation(180.0f);
				sf::FloatRect bounds = entity.getBounds();
				int left = (int)(std::floorf(bounds.left / scale));
				int right = (int)(std::ceilf((bounds.left + bounds.width) / scale)) - 1;
				int top = (int)(std::floorf(bounds.top / scale));
				int bottom = (int)(std::ceilf((bounds.top + bounds.height) / scale)) - 1;

				int end = 0;
				for(int y = top; y <= bottom; y++)
				{
					int x = left;
					while(Floor::getCurrentRoom().getTileType(x, y) == Room::TileType::floor && x > left - searchDist)
						x--;

					end = std::max(end, x);
				}

				searchArea = sf::FloatRect((float)(end + 1) * scale, bounds.top, bounds.left - (end + 1) * scale, bounds.height);

				if(Floor::player.getBounds().intersects(searchArea))
				{
					velCom->velocity = sf::Vector2f(-moveCom->aggressiveSpeed, 0.0f);
					entity.sprite.setRotation(180.0f);
					moveCom->forwardsDir = Left;
					moveCom->backwardsDir = Right;
					return true;
				}

				break;
			}
			case Right:
			{
				entity.sprite.setRotation(0.0f);
				sf::FloatRect bounds = entity.getBounds();
				int left = (int)(std::floorf(bounds.left / scale));
				int right = (int)(std::ceilf((bounds.left + bounds.width) / scale)) - 1;
				int top = (int)(std::floorf(bounds.top / scale));
				int bottom = (int)(std::ceilf((bounds.top + bounds.height) / scale)) - 1;

				int end = INT_MAX;
				for(int y = top; y <= bottom; y++)
				{
					int x = right;
					while(Floor::getCurrentRoom().getTileType(x, y) == Room::TileType::floor && x < right + searchDist)
						x++;

					end = std::min(end, x);
				}

				searchArea = sf::FloatRect(bounds.left + bounds.width, bounds.top, end * scale - (bounds.left + bounds.width), bounds.height);

				if(Floor::player.getBounds().intersects(searchArea))
				{
					velCom->velocity = sf::Vector2f(moveCom->aggressiveSpeed, 0.0f);
					entity.sprite.setRotation(0.0f);
					moveCom->forwardsDir = Right;
					moveCom->backwardsDir = Left;
					return true;
				}

				break;
			}
		}
	}

	entity.sprite.setRotation(rotation);

	return false;
}

void MovementSystem::calculatePacTurn(Entity& entity)
{
	std::shared_ptr<PacMoveCom> moveCom = std::dynamic_pointer_cast<PacMoveCom>(entity.getComponent(Component::ComponentType::PacMove));
	std::vector<Direction> availableDirs;

	for(int d = 0; d < 4; d++)
	{
		if(d == moveCom->backwardsDir || d == moveCom->forwardsDir)
			continue;

		if(evaluateDirection(entity, (Direction)d, moveCom->forwardsDir))
			availableDirs.push_back((Direction)d);
	}

	Direction newDir;
	if(availableDirs.size() == 0)
	{
		if(evaluateDirection(entity, moveCom->forwardsDir, moveCom->forwardsDir))
			newDir = moveCom->forwardsDir;
		else
			newDir = moveCom->backwardsDir;
	}
	else
		newDir = availableDirs[std::rand() % availableDirs.size()];

	std::shared_ptr<VelocityCom> velCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));

	switch(newDir)
	{
		case Up:
			velCom->velocity = sf::Vector2f(0.0f, -moveCom->passiveSpeed);
			moveCom->forwardsDir = Up;
			moveCom->backwardsDir = Down;
			entity.sprite.setRotation(-90.0f);
			break;
		case Down:
			velCom->velocity = sf::Vector2f(0.0f, moveCom->passiveSpeed);
			moveCom->forwardsDir = Down;
			moveCom->backwardsDir = Up;
			entity.sprite.setRotation(90.0f);
			break;
		case Left:
			velCom->velocity = sf::Vector2f(-moveCom->passiveSpeed, 0.0f);
			moveCom->forwardsDir = Left;
			moveCom->backwardsDir = Right;
			entity.sprite.setRotation(180.0f);
			break;
		case Right:
			velCom->velocity = sf::Vector2f(moveCom->passiveSpeed, 0.0f);
			moveCom->forwardsDir = Right;
			moveCom->backwardsDir = Left;
			entity.sprite.setRotation(0.0f);
			break;
	}
}

void MovementSystem::calculateWalkTurn(Entity& entity)
{
	std::shared_ptr<WalkMoveCom> moveCom = std::dynamic_pointer_cast<WalkMoveCom>(entity.getComponent(Component::ComponentType::WalkMove));
	std::vector<Direction> availableDirs;

	sf::FloatRect entityBounds = entity.getBounds();
	int scale = Room::tileSize * Utilities::getInstance().getScale();

	int left = (int)(std::floorf(entityBounds.left / scale));
	int right = (int)(std::ceilf((entityBounds.left + entityBounds.width) / scale)) - 1;
	int top = (int)(std::floorf(entityBounds.top / scale));
	int bottom = (int)(std::ceilf((entityBounds.top + entityBounds.height) / scale)) - 1;

	for(int d = 0; d < 4; d++)
	{
		if(d == moveCom->backwardDir || d == moveCom->forwardDir)
			continue;

		if(evaluateWalkDirection((Direction)d, left, right, top, bottom))
			availableDirs.push_back((Direction)d);
	}

	Direction newDir;
	if(availableDirs.size() == 0)
	{
		if(evaluateWalkDirection(moveCom->forwardDir, left, right, top, bottom))
			newDir = moveCom->forwardDir;
		else
			newDir = moveCom->backwardDir;
	}
	else
		newDir = availableDirs[std::rand() % availableDirs.size()];

	std::shared_ptr<VelocityCom> velCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));

	switch(newDir)
	{
		case Up:
			velCom->velocity = sf::Vector2f(0.0f, -moveCom->speed);
			moveCom->forwardDir = Direction::Up;
			moveCom->backwardDir = Direction::Down;
			break;
		case Down:
			velCom->velocity = sf::Vector2f(0.0f, moveCom->speed);
			moveCom->forwardDir = Direction::Down;
			moveCom->backwardDir = Direction::Up;
			break;
		case Left:
			velCom->velocity = sf::Vector2f(-moveCom->speed, 0.0f);
			moveCom->forwardDir = Direction::Left;
			moveCom->backwardDir = Direction::Right;
			break;
		case Right:
			velCom->velocity = sf::Vector2f(moveCom->speed, 0.0f);
			moveCom->forwardDir = Direction::Right;
			moveCom->backwardDir = Direction::Left;
			break;
	}
}

bool MovementSystem::evaluateWalkDirection(Direction d, int left, int right, int top, int bottom)
{
	switch(d)
	{
		case Direction::Up:
			if(top - 1 < 0)
				return false;

			for(int x = left; x <= right; x++)
				if(Floor::getCurrentRoom().getTileType(x, top - 1) != Room::TileType::floor)
					return false;

			return true;
		case Direction::Down:
			if(bottom + 1 > Room::height)
				return false;

			for(int x = left; x <= right; x++)
				if(Floor::getCurrentRoom().getTileType(x, bottom + 1) != Room::TileType::floor)
					return false;

			return true;
		case Direction::Left:
			if(left - 1 < 0)
				return false;

			for(int y = top; y <= bottom; y++)
				if(Floor::getCurrentRoom().getTileType(left - 1, y) != Room::TileType::floor)
					return false;

			return true;
		case Direction::Right:
			if(right + 1 > Room::width)
				return false;

			for(int y = top; y <= bottom; y++)
				if(Floor::getCurrentRoom().getTileType(right + 1, y) != Room::TileType::floor)
					return false;

			return true;
		default:
			return false;
	}
}

bool MovementSystem::evaluateDirection(Entity& entity, Direction d, Direction forwardDir)
{
	sf::FloatRect entityBounds = entity.getBounds();
	int scale = Room::tileSize * Utilities::getInstance().getScale();

	int left = (int)(std::floorf(entityBounds.left / scale));
	int right = (int)(std::ceilf((entityBounds.left + entityBounds.width) / scale)) - 1;
	int top = (int)(std::floorf(entityBounds.top / scale));
	int bottom = (int)(std::ceilf((entityBounds.top + entityBounds.height) / scale)) - 1;

	switch(d)
	{
		case Direction::Up:
		{
			for(int x = left; x <= right; x++)
			{
				if(Floor::getCurrentRoom().getTileType(x, top - 1) != Room::TileType::floor)
				{
					if(forwardDir == Up && entityBounds.top - top * scale >= 9)
						return true;

					return false;
				}
			}

			return true;
		}
		case Direction::Down:
		{
			for(int x = left; x <= right; x++)
			{
				if(Floor::getCurrentRoom().getTileType(x, bottom + 1) != Room::TileType::floor)
				{
					if(forwardDir == Down && (bottom + 1) * scale - (entityBounds.top + entityBounds.height) >= 9)
						return true;

					return false;
				}
			}

			return true;
		}
		case Direction::Left:
		{
			for(int y = top; y <= bottom; y++)
			{
				if(Floor::getCurrentRoom().getTileType(left - 1, y) != Room::TileType::floor)
				{
					if(forwardDir == Left && entityBounds.left - left * scale >= 9)
						return true;

					return false;
				}
			}

			return true;
		}
		case Direction::Right:
		{
			for(int y = top; y <= bottom; y++)
			{
				if(Floor::getCurrentRoom().getTileType(right + 1, y) != Room::TileType::floor)
				{
					if(forwardDir == Right && (right + 1) * scale - (entityBounds.left + entityBounds.width))
						return true;

					return false;
				}
			}

			return true;
		}

		default:
			return false;
	}
}