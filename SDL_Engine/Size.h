//
// Created by tuanzi on 18-12-11.
//

#ifndef SDLGAME_SIZE_H
#define SDLGAME_SIZE_H


#include <SDL2/SDL_rect.h>

class Size
{
public:
    int w;
    int h;
public:
    Size(int w=0,int h=0);
    Size(const Size& point);
    Size&operator=(const Size&point);
    Size&operator+(const Size&point);
    Size&operator-(const Size&point);
    Size&operator*(const Size&point);
    Size&operator/(const Size&point);
    friend Size&operator+=( Size&v1, const Size&v2);
    friend Size&operator-=( Size&v1, const Size&v2);
    friend Size&operator*=( Size&v1, const Size&v2);
    friend Size&operator/=( Size&v1, const Size&v2);
    ~Size();
    SDL_Rect asSDL_Rect();
};


#endif //SDLGAME_SIZE_H
