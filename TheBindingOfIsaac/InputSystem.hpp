#include "stdafx.h"
#include "System.hpp"
#include "Input.hpp"
#include "VelocityCom.hpp"
#include "PlayerProjectileCom.hpp"

class VelocityCom;

class InputSystem : public System
{
public:
	InputSystem(std::vector<Entity>& entityQueue);

	void update(std::vector<Entity>& entities);

private:
	std::vector<Entity>& entityQueue;
};