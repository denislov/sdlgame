#include "SDL_Engine/SDL_Engine.h"

#include "HelloWorld.h"

class GameScene : public Scene
{
  private:
    HelloWorld *hello;

  public:
    CREATE_FUN(GameScene);
    static Scene *createScene();
    bool init();
    GameScene(/* args */) { _name = "GameScene"; }
    ~GameScene()
    {
    }
};