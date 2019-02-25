#include "SDL_Engine/SDL_Engine.h"

class HelloWorld : public Layer
{
private:
  /* data */
  Sprite *example;
  void onTouch(SDL_Event *event);

public:
  HelloWorld(/* args */) { _name = "HelloWorld"; }
  ~HelloWorld()
  {
  }
  CREATE_FUN(HelloWorld);

  bool init();
};