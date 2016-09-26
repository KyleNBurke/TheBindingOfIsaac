#include "stdafx.h"
#include "PhysicsSystem.hpp"
#include "PacMoveCom.hpp"
#include "HealthCom.hpp"

PhysicsSystem::PhysicsSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void PhysicsSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::AccelDecel))
	{
		std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));
		std::shared_ptr<AccelerationCom> accelCom = std::dynamic_pointer_cast<AccelerationCom>(entity.getComponent(Component::ComponentType::AccelDecel));

		velocityCom->velocity += accelCom->acceleration;

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

		entity.position.x += velocityCom->velocity.x * deltaTime.asSeconds();
		entity.sprite.setPosition(entity.position);

		if(hasPitCollision || hasWallCollision)
			resolveCollisions(Direction::Horizontal, entity, hasPitCollision, hasWallCollision);

		entity.position.x = entity.sprite.getPosition().x;
		entity.sprite.setPosition(Utilities::getInstance().round(entity.position.x), entity.position.y);

		float leftToHalfInt = floor((entity.getBounds().left * 2.0f) + 0.5f) / 2.0f;
		if(std::floor(leftToHalfInt) != leftToHalfInt)
			entity.sprite.setPosition(Utilities::getInstance().round(entity.position.x + 0.5f) - 0.5f, entity.position.y);



		entity.position.y += velocityCom->velocity.y * deltaTime.asSeconds();
		entity.sprite.setPosition(entity.position);

		if(hasPitCollision || hasWallCollision)
			resolveCollisions(Direction::Vertical, entity, hasPitCollision, hasWallCollision);

		entity.position.y = entity.sprite.getPosition().y;
		entity.sprite.setPosition(entity.position.x, Utilities::getInstance().round(entity.position.y));

		float topToHalfInt = floor((entity.getBounds().top * 2.0f) + 0.5f) / 2.0f;
		if(std::floor(topToHalfInt) != topToHalfInt)
			entity.sprite.setPosition(entity.position.x, Utilities::getInstance().round(entity.position.y + 0.5f) - 0.5f);

	}

	if(&entity != &Floor::player && entity.hasComponent(Component::ComponentType::Health))
	{
		std::shared_ptr<HealthCom> healthCom = std::dynamic_pointer_cast<HealthCom>(Floor::player.getComponent(Component::ComponentType::Health));
		if(!healthCom->flashing && entity.getBounds().intersects(Floor::player.getBounds()))
		{
			std::shared_ptr<VelocityCom> velocityComEntity = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));
			std::shared_ptr<VelocityCom> velocityComPlayer = std::dynamic_pointer_cast<VelocityCom>(Floor::player.getComponent(Component::ComponentType::Velocity));

			float hDepth = Utilities::getInstance().getHorIntersectionDepth(entity.getBounds(), Floor::player.getBounds());
			float vDepth = Utilities::getInstance().getVertIntersectionDepth(entity.getBounds(), Floor::player.getBounds());

			if(abs(hDepth) < abs(vDepth))
				velocityComPlayer->velocity.x = velocityComEntity->velocity.x;
			else
				velocityComPlayer->velocity.y = velocityComEntity->velocity.y;

			healthCom->flashing = true;
			healthCom->health -= 1;
		}
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
				float depthX = Utilities::getInstance().getHorIntersectionDepth(entityBounds, tile);
				float depthY = Utilities::getInstance().getVertIntersectionDepth(entityBounds, tile);

				if(entity.hasComponent(Component::ComponentType::PacMove))
					pacMoveResolution(entity, direction, depthX, depthY);
				else if(entity.hasComponent(Component::ComponentType::Bouncer))
					bouncerResolution(entity, direction, depthX, depthY);
				else
					regularResolution(entity, direction, depthX, depthY);

				entityBounds = entity.getBounds();
			}
		}
	}
}


void PhysicsSystem::regularResolution(Entity& entity, Direction direction, float depthX, float depthY)
{
	if(direction == Horizontal && depthX != 0.0f)
	{
		entity.sprite.move(depthX, 0.0f);
		std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity))->velocity.x = 0.0f;
	}
	else if(direction == Vertical && depthY != 0.0f)
	{
		entity.sprite.move(0.0f, depthY);
		std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity))->velocity.y = 0.0f;
	}
}

void PhysicsSystem::pacMoveResolution(Entity& entity, Direction direction, float depthX, float depthY)
{
	if(direction == Horizontal && depthX != 0.0f)
	{
		entity.sprite.move(depthX, 0.0f);
		std::dynamic_pointer_cast<PacMoveCom>(entity.getComponent(Component::ComponentType::PacMove))->collided = true;
	}
	else if(direction == Vertical && depthY != 0.0f)
	{
		entity.sprite.move(0.0f, depthY);
		std::dynamic_pointer_cast<PacMoveCom>(entity.getComponent(Component::ComponentType::PacMove))->collided = true;
	}
}

void PhysicsSystem::bouncerResolution(Entity& entity, Direction direction, float depthX, float depthY)
{
	if(direction == Horizontal && depthX != 0.0f)
	{
		entity.sprite.move(depthX, 0.0f);
		std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));
		velocityCom->velocity.x = -velocityCom->velocity.x;
	}
	else if(direction == Vertical && depthY != 0.0f)
	{
		entity.sprite.move(0.0f, depthY);
		std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));
		velocityCom->velocity.y = -velocityCom->velocity.y;
	}
}