#include "stdafx.h"
#include "Utilities.hpp"
#include "Entity.hpp"

class Assemblages
{
public:
	static Assemblages& getInstance();

	void initialize();

	Entity createPlayer(sf::Vector2f position);
	Entity createPlayerDamageStain(sf::Vector2f position);
	Entity createPlayerProjectile(sf::Vector2f position, sf::Vector2f velocity);
	Entity createRegularProjectile(sf::Vector2f position, sf::Vector2f direction);
	Entity createTurret(sf::Vector2f position);
	Entity createBouncer(sf::Vector2f position, sf::Vector2f direction);
	Entity createParticle(sf::Vector2f position, sf::IntRect textureRect, sf::Vector2f velocity, float lifetime);
	Entity createPac(sf::Vector2f position, Direction initialDirection);
	Entity createEnemyDeath(sf::Vector2f position);
	Entity createEnemyDeathStain(sf::Vector2f position);
	Entity createEnemyDamageStain(sf::Vector2f position);
	Entity createProjectileDeath(sf::Vector2f position);

private:
	Assemblages();
	Assemblages(const Assemblages&);
	void operator=(const Assemblages&);

	sf::Texture playerSpriteSheet;
	sf::Texture projectilesSpriteSheet;
	sf::Texture enemySpriteSheet;
	sf::Texture particleSpriteSheet;
};