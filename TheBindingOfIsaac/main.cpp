#include "stdafx.h"
#include "GameManager.hpp"

int main()
{
	GameManager::getInstance().initialize();
	GameManager::getInstance().gameLoop();

	return 0;
}