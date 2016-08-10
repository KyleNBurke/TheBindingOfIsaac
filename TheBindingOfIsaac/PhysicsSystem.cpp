#include "stdafx.h"
#include "PhysicsSystem.hpp"
#include "PacMoveCom.hpp"

PhysicsSystem::PhysicsSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void PhysicsSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::AccelDecel))
	{
		std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));
		std::shared_ptr<AccelDecelCom> accelDecelCom = std::dynamic_pointer_cast<AccelDecelCom>(entity.getComponent(Component::ComponentType::AccelDecel));

		velocityCom->velocity += ((velocityCom->direction * accelDecelCom->maxSpeed) - velocityCom->velocity) * accelDecelCom->acceleration;

		if(std::abs(velocityCom->velocity.x) < 0.05)
			velocityCom->velocity.x = 0.0f;
		if(std::abs(velocityCom->velocity.y) < 0.05)
			velocityCom->velocity.y = 0.0f;
	}

	if(entity.hasComponent(Component::ComponentType::Velocity))
	{
		int tileSize = Room::tileSize * Utilities::getInstance().getScale();
		std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));
		bool hasPitCollision = entity.hasComponent(Component::ComponentType::PitCollision);
		bool hasWallCollision = entity.hasComponent(Component::ComponentType::WallCollision);

		entity.sprite.move(velocityCom->velocity.x * deltaTime.asSeconds(), 0.0f);
		sf::Vector2f position = entity.sprite.getPosition();
		entity.sprite.setPosition(Utilities::getInstance().round(position.x), position.y);

		float leftToHalfInt = floor((entity.getBounds().left * 2.0f) + 0.5f) / 2.0f;
		if(std::floor(leftToHalfInt) != leftToHalfInt)
			entity.sprite.setPosition(Utilities::getInstance().round(position.x + 0.5f) - 0.5f, position.y);

		if(hasPitCollision || hasWallCollision)
			resolveCollisions(Direction::Horizontal, entity, hasPitCollision, hasWallCollision);


		entity.sprite.move(0.0f, velocityCom->velocity.y * deltaTime.asSeconds());
		position = entity.sprite.getPosition();
		entity.sprite.setPosition(position.x, Utilities::getInstance().round(position.y));

		float topToHalfInt = floor((entity.getBounds().top * 2.0f) + 0.5f) / 2.0f;
		if(std::floor(topToHalfInt) != topToHalfInt)
			entity.sprite.setPosition(position.x, Utilities::getInstance().round(position.y + 0.5f) - 0.5f);

		if(hasPitCollision || hasWallCollision)
			resolveCollisions(Direction::Vertical, entity, hasPitCollision, hasWallCollision);
	}
}

void PhysicsSystem::resolveCollisions(Direction direction, Entity& entity, bool hasPitCollision, bool hasWallCollision)
{
	sf::FloatRect entityBounds = entity.getBounds();
	int scale = Room::tileSize * Utilities::getInstance().getScale();

	int left = (int)(std::floorf(entityBounds.left / scale));
	int right = (int)(std::ceilf((entityBounds.left + entityBounds.width) / scale)) - 1;
	int top = (int)(std::floorf(entityBounds.top / scale));
	int bottom = (int)(std::ceilf((entityBounds.top + entityBounds.height) / scale)) - 1;

	for(int x = left; x <= right; x++)
	{
		for(int y = top; y <= bottom; y++)
		{
			Room::TileType tileType = Floor::getCurrentRoom().getTileType(x, y);

			if((hasPitCollision && tileType == Room::TileType::pit) || (hasWallCollision && tileType == Room::TileType::wall))
			{
				sf::FloatRect tile((float)x * scale, (float)y * scale, (float)scale, (float)scale);
				float depth;

				if(direction == Direction::Horizontal)
				{
					depth = Utilities::getInstance().getHorIntersectionDepth(entityBounds, tile);

					if(depth != 0.0f)
					{
						entity.sprite.move(depth, 0.0f);
						std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity))->velocity.x = 0.0f;
						entityBounds = entity.getBounds();

						if(entity.hasComponent(Component::ComponentType::PacMove))
							std::dynamic_pointer_cast<PacMoveCom>(entity.getComponent(Component::ComponentType::PacMove))->collided = true;
					}
				}
				else
				{
					depth = Utilities::getInstance().getVertIntersectionDepth(entityBounds, tile);

					if(depth != 0.0f)
					{
						entity.sprite.move(0.0f, depth);
						std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity))->velocity.y = 0.0f;
						entityBounds = entity.getBounds();

						if(entity.hasComponent(Component::ComponentType::PacMove))
							std::dynamic_pointer_cast<PacMoveCom>(entity.getComponent(Component::ComponentType::PacMove))->collided = true;
					}
				}
			}
		}
	}
}