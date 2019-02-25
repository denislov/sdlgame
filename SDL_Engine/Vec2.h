//
// Created by tuanzi on 18-12-11.
//

#ifndef SDLGAME_Vec2_H
#define SDLGAME_Vec2_H


#include <SDL2/SDL_rect.h>

class Vec2
{
public:
    float x;
    float y;
public:
    Vec2(float x=0,float y=0);
    Vec2(const Vec2& Vec2);
    Vec2&operator=(const Vec2&Vec2);
    Vec2&operator+(const Vec2&Vec2);
    Vec2&operator-(const Vec2&Vec2);
    Vec2&operator*(const Vec2&Vec2);
    Vec2&operator/(const Vec2&Vec2);
    friend Vec2&operator+=( Vec2&v1, const Vec2&v2);
    friend Vec2&operator-=( Vec2&v1, const Vec2&v2);
    friend Vec2&operator*=( Vec2&v1, const Vec2&v2);
    friend Vec2&operator/=( Vec2&v1, const Vec2&v2);
    ~Vec2();
    SDL_Point asSDL_Point();
};


#endif //SDLGAME_Vec2_H
