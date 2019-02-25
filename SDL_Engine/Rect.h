//
// Created by tuanzi on 18-12-11.
//

#ifndef SDLGAME_RECT_H
#define SDLGAME_RECT_H

#include <SDL_rect.h>
#include "Vec2.h"
#include "Size.h"

class Rect
{
  public:
    Vec2 origin;
    Size size;

  public:
    Rect(int x = 0, int y = 0, int width = 0, int height = 0);
    Rect(const Rect &rect);
    Rect(const SDL_Rect &other);
    Rect(const Vec2 &origin, const Size &size);
    Rect(float x, float y, const Size &size);
    Rect(const Vec2 &origin, float w, float h);
    ~Rect();
    Rect &operator=(const Rect &rect);
    Rect &operator+(const Rect &rect);
    Rect &operator-(const Rect &rect);
    Rect &operator*(const Rect &rect);
    Rect &operator/(const Rect &rect);
    Rect &scale(float x, float y);
    Rect &scale(const Vec2 &scale);
    //return SDL_Rect
    SDL_Rect asSDL_Rect();
};

#endif //SDLGAME_RECT_H
