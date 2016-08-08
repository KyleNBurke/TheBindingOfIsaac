#include "stdafx.h"
#include "MovementSystem.hpp"
#include "PacMoveCom.hpp"
#include "Floor.hpp"
#include "VelocityCom.hpp"
#include "AnimationCom.hpp"

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
						calculateTurn(entity);

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
					calculateTurn(entity);
					moveCom->collided = false;
					animCom->currentState = 0;
				}
				break;
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

void MovementSystem::calculateTurn(Entity& entity)
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