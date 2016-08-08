#include "stdafx.h"
#include "Utilities.hpp"
#include "Entity.hpp"
#include "PlayerControlledCom.hpp"
#include "VelocityCom.hpp"
#include "AccelDecelCom.hpp"
#include "PitCollisionCom.hpp"
#include "WallCollisionCom.hpp"
#include "ProjectileCom.hpp"
#include "HealthCom.hpp"
#include "TurretShotCom.hpp"
#include "PlayerShotCom.hpp"
#include "BouncerCom.hpp"
#include "LifetimeCom.hpp"
#include "AnimationCom.hpp"
#include "AnimationStateStatic.hpp"
#include "AnimationStateDynamic.hpp"
#include "PacMoveCom.hpp"

class Assemblages
{
public:
	static Assemblages& getInstance();

	void initialize();

	Entity createPlayer(sf::Vector2f position);
	Entity createPlayerProjectile(sf::Vector2f position, sf::Vector2f velocity);
	Entity createRegularProjectile(sf::Vector2f position, sf::Vector2f direction);
	Entity createTurret(sf::Vector2f position);
	Entity createBouncer(sf::Vector2f position, sf::Vector2f direction);
	Entity createParticle(sf::Vector2f position, sf::IntRect textureRect, sf::Vector2f velocity, float lifetime);
	Entity createPac(sf::Vector2f position, Direction initialDirection);

private:
	Assemblages();
	Assemblages(const Assemblages&);
	void operator=(const Assemblages&);

	sf::Texture playerSpriteSheet;
	sf::Texture projectilesSpriteSheet;
	sf::Texture enemySpriteSheet;
	sf::Texture particleSpriteSheet;
};