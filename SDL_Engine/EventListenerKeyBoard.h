#ifndef _SDL_EventListenerKeyBoard_H
#define _SDL_EventListenerKeyBoard_H
#include "EventListener.h"
#include "SETool.h"
#include <SDL.h>
class EventListenerKeyBoard : public EventListener
{
  public:
    std::function<void(SDL_Keycode, SDL_Event *)> onKeyPressed;
    std::function<void(SDL_Keycode, SDL_Event *)> onKeyReleased;
    std::function<void(SDL_Keycode, SDL_Event *)> onKeyEvent;

  public:
    EventListenerKeyBoard();
    ~EventListenerKeyBoard();
    CREATE_FUN(EventListenerKeyBoard);
    bool init();

    virtual EventListenerKeyBoard *clone();
    virtual bool checkAvailable() const;
};

#endif