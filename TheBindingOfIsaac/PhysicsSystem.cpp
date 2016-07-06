#include "stdafx.h"
#include "PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void PhysicsSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::AccelDecel))
	{
		std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));
		std::shared_ptr<AccelDecelCom> accelDecelCom = std::dynamic_pointer_cast<AccelDecelCom>(entity.getComponent(Component::ComponentType::AccelDecel));

		velocityCom->velocity.x += velocityCom->direction.x * accelDecelCom->acceleration;
		velocityCom->velocity.y += velocityCom->direction.y * accelDecelCom->acceleration;

		velocityCom->velocity *= accelDecelCom->deceleration;
	}

	if(entity.hasComponent(Component::ComponentType::Velocity))
	{
		int tileSize = Room::tileSize * Utilities::getInstance().getScale();
		std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));
		bool hasPitCollision = entity.hasComponent(Component::ComponentType::PitCollision);
		bool hasWallCollision = entity.hasComponent(Component::ComponentType::WallCollision);
			
		entity.position.x += Utilities::getInstance().round(velocityCom->velocity.x * deltaTime.asSeconds());

		if(hasPitCollision || hasWallCollision) {
			resolveCollisions(Direction::Horizontal, entity, hasPitCollision, hasWallCollision);
		}

		entity.position.y += Utilities::getInstance().round(velocityCom->velocity.y * deltaTime.asSeconds());

		if(hasPitCollision || hasWallCollision)
		{
			resolveCollisions(Direction::Vertical, entity, hasPitCollision, hasWallCollision);
		}

		entity.sprite.setPosition(entity.position);
	}

	if(entity.hasComponent(Component::ComponentType::Bouncer))
	{
		sf::FloatRect entityBounds(entity.sprite.getGlobalBounds());
		int scale = Room::tileSize * Utilities::getInstance().getScale();

		int left = (int)(std::floorf(entityBounds.left / scale));
		int right = (int)(std::ceilf((entityBounds.left + entityBounds.width) / scale)) - 1;
		int top = (int)(std::floorf(entityBounds.top / scale));
		int bottom = (int)(std::ceilf((entityBounds.top + entityBounds.height) / scale)) - 1;

		for(int x = left; x <= right; x++)
		{
			for(int y = top; y <= bottom; y++)
			{
				if(Floor::getCurrentRoom().getTileType(x, y) == Room::TileType::wall)
				{
					sf::IntRect tile(x * scale, y * scale, scale, scale);
					std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));

					float horzDepth = Utilities::getInstance().getHorIntersectionDepth((sf::IntRect)entityBounds, tile);
					float vertDepth = Utilities::getInstance().getVertIntersectionDepth((sf::IntRect)entityBounds, tile);

					if(std::abs(horzDepth) < std::abs(vertDepth))
					{
						velocityCom->velocity.x = -velocityCom->velocity.x;
						return;
					}
					else
					{
						velocityCom->velocity.y = -velocityCom->velocity.y;
						return;
					}
					
				}
			}
		}
	}
}

void PhysicsSystem::resolveCollisions(Direction direction, Entity& entity, bool hasPitCollision, bool hasWallCollision)
{
	sf::FloatRect entityBounds = getEntityBounds(entity);
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
				sf::IntRect tile(x * scale, y * scale, scale, scale);
				float depth;

				if(direction == Direction::Horizontal)
				{
					depth = Utilities::getInstance().getHorIntersectionDepth((sf::IntRect)entityBounds, tile);

					if(depth != 0.0f)
					{
						entity.position.x += depth;
						std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity))->velocity.x = 0.0f;
						entityBounds = getEntityBounds(entity);
					}
				}
				else
				{
					depth = Utilities::getInstance().getVertIntersectionDepth((sf::IntRect)entityBounds, tile);

					if(depth != 0.0f)
					{
						entity.position.y += depth;
						std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity))->velocity.y = 0.0f;
						entityBounds = getEntityBounds(entity);
					}
				}
			}
		}
	}
}

sf::FloatRect PhysicsSystem::getEntityBounds(const Entity& entity)
{
	return sf::FloatRect(entity.position.x, entity.position.y, entity.sprite.getGlobalBounds().width, entity.sprite.getGlobalBounds().height);
}