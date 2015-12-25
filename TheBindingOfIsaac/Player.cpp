#include "stdafx.h"
#include "Player.hpp"
#include "Utilities.hpp"
#include "Input.hpp"
#include "Map.hpp"

Player::Player() : sprite(spriteSheet, sf::IntRect(0, 0, 7, 7)), acceleration(70.0f), deceleration(0.85f)
{
	spriteSheet.loadFromFile("Player.png");
	sprite.setScale((float)Utilities::getInstance().getScale(), (float)Utilities::getInstance().getScale());

	position = sf::Vector2f(250.0f, 200.0f);
}

void Player::update(sf::Time deltaTime)
{
	sf::Vector2i direction(0, 0);

	if(Input::getInstance().keyHeld(sf::Keyboard::Key::W))
		direction.y = -1;

	if(Input::getInstance().keyHeld(sf::Keyboard::Key::S))
		direction.y = 1;

	if(Input::getInstance().keyHeld(sf::Keyboard::Key::A))
		direction.x = -1;

	if(Input::getInstance().keyHeld(sf::Keyboard::Key::D))
		direction.x = 1;

	velocity.x = (velocity.x + acceleration * direction.x) * deceleration;
	velocity.y = (velocity.y + acceleration * direction.y) * deceleration;

	position.x += Utilities::getInstance().round(velocity.x * deltaTime.asSeconds());
	resolveCollisions(Direction::horizontal);

	position.y += Utilities::getInstance().round(velocity.y * deltaTime.asSeconds());
	resolveCollisions(Direction::vertical);

	sprite.setPosition(position);
}

void Player::resolveCollisions(Player::Direction direction)
{
	sf::FloatRect playerBounds = getPlayerBounds();
	int scale = Room::tileSize * Utilities::getInstance().getScale();

	int left = (int)(std::floorf(playerBounds.left / scale));
	int right = (int)(std::ceilf((playerBounds.left + playerBounds.width) / scale)) - 1;
	int top = (int)(std::floorf(playerBounds.top / scale));
	int bottom = (int)(std::ceilf((playerBounds.top + playerBounds.height) / scale)) - 1;

	for(int x = left; x <= right; x++)
	{
		for(int y = top; y <= bottom; y++)
		{
			Room::TileType tileType = Map::getCurrentRoom().getTileType(x, y);

			if(tileType == Room::TileType::wall || tileType == Room::TileType::pit)
			{
				sf::IntRect tile(x * scale, y * scale, scale, scale);
				std::cout << direction<< std::endl;

				float depth;
				if(direction == Direction::horizontal)
				{
					depth = Utilities::getInstance().getHorIntersectionDepth((sf::IntRect)playerBounds, tile);

					if(depth != 0.0f)
					{
						position.x += depth;
						velocity.x = 0.0f;
						playerBounds = getPlayerBounds();
					}
				}
				else
				{
					depth = Utilities::getInstance().getVertIntersectionDepth((sf::IntRect)playerBounds, tile);

					if(depth != 0.0f)
					{
						position.y += depth;
						velocity.y = 0.0f;
						playerBounds = getPlayerBounds();
					}
				}
			}
		}
	}
}

sf::FloatRect Player::getPlayerBounds() const
{
	return sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}