#include "EventListenerTouch.h"
EventListenerTouch::EventListenerTouch(/* args */) : onTouch(nullptr),
                                                     onTouchDown(nullptr),
                                                     onTouchUp(nullptr)
{
    _name = "EventListenerTouch";
}

EventListenerTouch::~EventListenerTouch()
{
}
bool EventListenerTouch::init()
{
    _listenerID = "EventListenerTouch";
    return true;
}

EventListenerTouch *EventListenerTouch::clone()
{
    auto listener = EventListenerTouch::create();
    listener->_bRegistered = this->_bRegistered;
    listener->_paused = this->_paused;
    listener->_bindNode = this->_bindNode;
    return listener;
}
bool EventListenerTouch::checkAvailable() const
{
    return isRegistered() && !isPaused() && getBindNode();
}