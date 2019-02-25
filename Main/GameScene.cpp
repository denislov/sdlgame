#include "GameScene.h"

Scene *GameScene::createScene()
{
    return GameScene::create();
}
bool GameScene::init()
{
    hello = HelloWorld::create();
    _contentSize = TheDirector::getInstance()->getVisibleSize();
    this->addChild(hello);
    return true;
}