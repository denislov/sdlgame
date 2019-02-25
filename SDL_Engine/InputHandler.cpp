#include "InputHandler.h"
#include <SDL.h>
#include "Director.h"
#include "EventListenerKeyBoard.h"
#include "EventListenerTouch.h"
InputHandler::InputHandler() { _name = "InputHandler"; }
InputHandler::~InputHandler() {}
void InputHandler::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            TheDirector::getInstance()->setRunning(false);
            break;
        case SDL_KEYUP:
        case SDL_KEYDOWN:
            onKeyEvent(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEMOTION:
            onMouseEvent(event);
        default:
            break;
        }
    }
}
void InputHandler::onMouseEvent(SDL_Event &event)
{
    auto onEvent = [](EventListenerTouch *listener, SDL_Event &event) {
        if (listener->checkAvailable())
        {
            if (event.type == SDL_MOUSEBUTTONDOWN && listener->onTouchDown)
                listener->onTouchDown(&event);
            if (event.type == SDL_MOUSEBUTTONUP && listener->onTouchUp)
                listener->onTouchUp(&event);
            if (listener->onTouch)
                listener->onTouch(&event);
        }
    };
    auto listeners = getListeners("EventListenerTouch");
    if (listeners)
        for (unsigned int i = 0; i < listeners->size(); i++)
        {
            auto listener = static_cast<EventListenerTouch *>(listeners->at(i));
            onEvent(listener, event);
        }
}
void InputHandler::onKeyEvent(SDL_Event &event)
{
    auto onEvent = [](EventListenerKeyBoard *listener, SDL_Event &event) {
        if (listener->checkAvailable())
        {
            SDL_Keycode key = event.key.keysym.sym;
            if (event.type == SDL_KEYDOWN && listener->onKeyPressed)
                listener->onKeyPressed(key, &event);
            if (event.type == SDL_KEYUP && listener->onKeyReleased)
                listener->onKeyReleased(key, &event);
            if (listener->onKeyEvent)
                listener->onKeyEvent(key, &event);
        }
    };
    auto listeners = getListeners("EventListenerKeyBoard");
    if (listeners != nullptr)
        for (unsigned int i = 0; i < listeners->size(); i++)
        {
            auto listener = static_cast<EventListenerKeyBoard *>(listeners->at(i));
            onEvent(listener, event);
        }
}
std::vector<EventListener *> *InputHandler::getListeners(const std::string listenerID)
{
    auto iter = _listeners.find(listenerID);
    return iter == _listeners.end() ? nullptr : iter->second;
}

void InputHandler::addEventListener(Node *node, EventListener *listener)
{
    std::string listenerID = listener->getListenerID();

    std::vector<EventListener *> *listeners = nullptr;

    auto iter = _listeners.find(listenerID);
    if (iter == _listeners.end())
    {
        listeners = new std::vector<EventListener *>();
        _listeners.insert(std::make_pair(listenerID, listeners));
    }
    else
        listeners = iter->second;
    listener->setPaused(false);
    listeners->push_back(listener);
    listener->setBindNode(node);
    listener->setRegistered(true);
    listener->retain();
}
void InputHandler::removeEventListenerForNode(const Node *node)
{
    for (auto listenerIter = _listeners.begin(); listenerIter != _listeners.end();)
    {
        std::vector<EventListener *> *listenerVec = listenerIter->second;
        for (auto iter = listenerVec->begin(); iter != listenerVec->end();)
        {
            auto listener = *iter;

            if (listener->getBindNode() == node)
            {
                iter = listenerVec->erase(iter);

                listener->setRegistered(false);
                listener->release();
            }
            else
                ++iter;
        }
        listenerIter++;
    }
}

void InputHandler::pauseEventListenerForNode(const Node *node)
{
    for (auto listenerIter = _listeners.begin(); listenerIter != _listeners.end();)
    {
        std::vector<EventListener *> *listenerVec = listenerIter->second;
        for (auto iter = listenerVec->begin(); iter != listenerVec->end();)
        {
            auto listener = *iter;

            if (listener->getBindNode() == node)
            {

                listener->setPaused(true);
            }
            ++iter;
        }
        listenerIter++;
    }
}
void InputHandler::resumeEventListenerForNode(const Node *node)
{
    for (auto listenerIter = _listeners.begin(); listenerIter != _listeners.end();)
    {
        std::vector<EventListener *> *listenerVec = listenerIter->second;
        for (auto iter = listenerVec->begin(); iter != listenerVec->end();)
        {
            auto listener = *iter;

            if (listener->getBindNode() == node)
            {

                listener->setPaused(false);
            }
            ++iter;
        }
        listenerIter++;
    }
}