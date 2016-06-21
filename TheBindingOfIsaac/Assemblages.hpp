#include "stdafx.h"
#include "Utilities.hpp"
#include "Entity.hpp"
#include "PlayerControlledCom.hpp"
#include "VelocityCom.hpp"
#include "AccelDecelCom.hpp"
#include "PitCollisionCom.hpp"
#include "WallCollisionCom.hpp"
#include "PlayerProjectileCom.hpp"
#include "EnemyProjectileCom.hpp"
#include "HealthCom.hpp"
#include "TurretShotCom.hpp"
#include "PlayerShotCom.hpp"

class Assemblages
{
public:
	static Assemblages& getInstance();

	void initialize();

	Entity createPlayer();
	Entity createPlayerProjectile(sf::Vector2f position, sf::Vector2f velocity);
	Entity createRegularProjectile(sf::Vector2f position, sf::Vector2f direction);
	Entity createTurret(sf::Vector2f position);

private:
	Assemblages();
	Assemblages(const Assemblages&);
	void operator=(const Assemblages&);

	sf::Texture playerSpriteSheet;
	sf::Texture projectilesSpriteSheet;
	sf::Texture enemySpriteSheet;
};