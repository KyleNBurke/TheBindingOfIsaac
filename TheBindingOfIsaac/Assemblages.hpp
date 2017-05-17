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
	Entity createEnemyBomb(sf::Vector2f position);
	Entity createEnemySlideBomb(sf::Vector2f position, sf::Vector2f initialVelocity);
	Entity createEnemyRegularProjectile(sf::Vector2f position, sf::Vector2f direction);
	Entity createEnemyCollisionProjectile(sf::Vector2f position, sf::Vector2f direction);
	Entity createBouncer(sf::Vector2f position);
	Entity createPac(sf::Vector2f position, Direction initialDirection);
	Entity createDirectJimmy(sf::Vector2f position);
	Entity createRoundJimmy(sf::Vector2f position);
	Entity createAttackFly(sf::Vector2f position);
	Entity createAttackFlySpawner(sf::Vector2f position);
	Entity createBombFly(sf::Vector2f position);
	Entity createBombFlySpawner(sf::Vector2f position);
	Entity createDaddyFly(sf::Vector2f position);
	Entity createRandomDashie(sf::Vector2f position);
	Entity createDirectDashie(sf::Vector2f position);
	Entity createSpinny(sf::Vector2f position);
	Entity createBombSpinny(sf::Vector2f position);
	Entity createWalker(sf::Vector2f position);
	Entity createRoundShotWalker(sf::Vector2f position);
	Entity createFastWalker(sf::Vector2f position);
	Entity createEnemyDeath(sf::Vector2f position);
	Entity createEnemyDeathStain(sf::Vector2f position);
	Entity createProjectileDeath(sf::Vector2f position);
	Entity createBlockDestruction(sf::Vector2f position);
	Entity createExplosion(sf::Vector2f position);
	Entity createExplosionStain(sf::Vector2f position);
	Entity createROF_UpItem(sf::Vector2f position);
	Entity createPlusTenBombsItem(sf::Vector2f position);
	Entity createRangeUpItem(sf::Vector2f position);
	Entity createProjectileBombsItem(sf::Vector2f position);
	Entity createPlusOneHeartItem(sf::Vector2f position);
	Entity createPlusOneBomb(sf::Vector2f position);

	float playerProjectileLifetime;

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