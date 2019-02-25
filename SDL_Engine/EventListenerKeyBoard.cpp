#include "EventListenerKeyBoard.h"
#include "PoolManager.h"

EventListenerKeyBoard::EventListenerKeyBoard() : onKeyEvent(nullptr),
                                                 onKeyPressed(nullptr),
                                                 onKeyReleased(nullptr)
{
    _name = "EventListenerKeyBoard";
}
EventListenerKeyBoard::~EventListenerKeyBoard() {}

bool EventListenerKeyBoard::init()
{
    _listenerID = "EventListenerKeyBoard";
    return true;
}
EventListenerKeyBoard *EventListenerKeyBoard::clone()
{
    auto listener = EventListenerKeyBoard::create();
    listener->_bRegistered = this->_bRegistered;
    listener->_paused = this->_paused;
    listener->_bindNode = this->_bindNode;
    return listener;
}

bool EventListenerKeyBoard::checkAvailable() const
{
    return isRegistered() && !isPaused() && getBindNode();
}
