#include "HelloWorld.h"
#include "pugixml/pugixml.hpp"
bool HelloWorld::init()
{
     auto tileLayer = TileLayer::create();
     tileLayer->loadMapWithFile("map.tmx");
     this->addChild(tileLayer);
//    example = Sprite::create();
//
//    example->load("example.jpg");
//
//    example->setPosition(300, 300);
//
//    example->setScale(0.5, 0.5);
//
//    auto example1 = example->clone();
//    example->setRotation(30.f);
//    this->addChild(example, 1);
//    this->addChild(example1, 0);

//    auto listener = EventListenerTouch::create();
//
//    listener->onTouch = SDL_CALLBACK_1(HelloWorld::onTouch, this);
//    addEventListener(listener);
    return true;
}

void HelloWorld::onTouch(SDL_Event *event)
{
    // if (event->type == SDL_MOUSEBUTTONDOWN)
    // {
    //     example->setPosition(event->motion.x, event->motion.y);
    // }
    /*  if (event->type == SDL_KEYDOWN)
        switch (key)
        {
        case SDLK_s:
            TheDirector::getInstance()->getRenderer()->setBgColor(Color::YELLOW);
            example->setPosition(example->getPosition() + Vec2(0, 10));
            break;
        case SDLK_w:
            example->setPosition(example->getPosition() - Vec2(0, 10));
            break;
        case SDLK_d:
            example->setPosition(example->getPosition() + Vec2(10, 0));
            break;
        case SDLK_a:
            example->setPosition(example->getPosition() - Vec2(10, 0));
            break;
        default:
            break;
        } */
}