#ifndef _SDL_InputHandler_H
#define _SDL_InputHandler_H
#include <map>
#include <string>
#include <vector>
#include "EventListener.h"
#include "Node.h"
#include <SDL2/SDL.h>
class InputHandler : public Object
{
private:
  /* data */
  std::map<std::string, std::vector<EventListener *> *> _listeners;
  void onKeyEvent(SDL_Event &event);
  void onMouseEvent(SDL_Event &event);

public:
  InputHandler();
  ~InputHandler();

  void update();

  std::vector<EventListener *> *getListeners(const std::string listenerID);

  void addEventListener(Node *node, EventListener *listener);
  void removeEventListenerForNode(const Node *node);
  void pauseEventListenerForNode(const Node *node);
  void resumeEventListenerForNode(const Node *node);
};
#endif