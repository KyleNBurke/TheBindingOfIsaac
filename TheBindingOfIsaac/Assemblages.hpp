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
	Entity createPlayerBomb(sf::Vector2f position);
	Entity createRegularProjectile(sf::Vector2f position, sf::Vector2f direction);
	Entity createBouncer(sf::Vector2f position, sf::Vector2f direction);
	Entity createParticle(sf::Vector2f position, sf::IntRect textureRect, sf::Vector2f velocity, float lifetime);
	Entity createPac(sf::Vector2f position, Direction initialDirection);
	Entity createJimmy(sf::Vector2f position);
	Entity createEnemyDeath(sf::Vector2f position);
	Entity createEnemyDeathStain(sf::Vector2f position);
	Entity createEnemyDamageStain(sf::Vector2f position);
	Entity createProjectileDeath(sf::Vector2f position);
	Entity createBlockDestruction(sf::Vector2f position);
	Entity createExplosion(sf::Vector2f position);
	Entity createExplosionStain(sf::Vector2f position);
	Entity createROF_UpItem(sf::Vector2f position);
	Entity createPlusTenBombsItem(sf::Vector2f position);

private:
	Assemblages();
	Assemblages(const Assemblages&);
	void operator=(const Assemblages&);

	sf::Texture playerSpriteSheet;
	sf::Texture projectilesSpriteSheet;
	sf::Texture enemySpriteSheet;
	sf::Texture particleSpriteSheet;
	sf::Texture itemsSpriteSheet;
};