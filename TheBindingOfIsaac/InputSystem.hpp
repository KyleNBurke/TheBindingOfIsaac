#include "stdafx.h"
#include "System.hpp"
#include "Input.hpp"
#include "VelocityCom.hpp"

class VelocityCom;

class InputSystem : public System
{
public:
	InputSystem();

	void update(std::vector<Entity>& entities);
};