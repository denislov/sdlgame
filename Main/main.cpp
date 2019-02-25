#include <iostream>
#include <cstdlib>
#include "GameScene.h"
#include "pugixml/pugixml.hpp"
int main(int argc, char *argv[])
{

	if (TheDirector::getInstance()->init())
	{
		TheFileUtils::getInstance()->addSearchPath("Resource");
		TheDirector::getInstance()->runWithScene(GameScene::createScene());
		while (TheDirector::getInstance()->isRunning())
		{
			TheDirector::getInstance()->update();
			ThePoolManager::getInstance()->getCurrentObjectPool()->clear();
		}

		TheDirector::getInstance()->purge();
		TheFileUtils::getInstance()->purge();
		ThePoolManager::getInstance()->purge();
	}

	return 0;
}
