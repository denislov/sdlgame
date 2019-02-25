
#if !defined(_EVENTTOUCH_H)
#define _EVENTTOUCH_H
#include <SDL.h>
#include <functional>
#include "EventListener.h"
class EventListenerTouch : public EventListener
{
  public:
    /* data */
    std::function<void(SDL_Event *)> onTouchDown;
    std::function<void(SDL_Event *)> onTouchUp;
    std::function<void(SDL_Event *)> onTouch;

  public:
    EventListenerTouch(/* args */);
    ~EventListenerTouch();
    CREATE_FUN(EventListenerTouch);
    bool init();

    virtual EventListenerTouch *clone();
    virtual bool checkAvailable() const;
};

#endif // _EVENTTOUCH_H
