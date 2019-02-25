//
// Created by tuanzi on 18-12-11.
//

#ifndef SDLGAME_SCENE_H
#define SDLGAME_SCENE_H

#include "Node.h"
class Scene:public Node
{
public:
    Scene();
    virtual ~Scene();
    CREATE_FUN(Scene);
    virtual bool init();

};


#endif //SDLGAME_SCENE_H
