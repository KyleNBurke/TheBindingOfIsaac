#include "stdafx.h"
#include "GameManager.hpp"
#include <Windows.h>

//int main()
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	GameManager::getInstance().initialize();
	GameManager::getInstance().gameLoop();

	return 0;
}