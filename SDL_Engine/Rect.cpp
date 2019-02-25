//
// Created by tuanzi on 18-12-11.
//

#include "Rect.h"

Rect::Rect(int x, int y, int width, int height)
{
    origin.x = x;
    origin.y = y;
    size.w = width;
    size.h = height;
}

Rect::Rect(const Rect &rect)
{
    origin = rect.origin;
    size = rect.size;
}

Rect::Rect(const SDL_Rect &other)
{
    origin.x = other.x;
    origin.y = other.y;
    size.w = other.w;
    size.h = other.h;
}

Rect::Rect(const Vec2 &origin, const Size &size)
{
    this->origin = origin;
    this->size = size;
}

Rect::Rect(float x, float y, const Size &size)
{
    origin.x = x;
    origin.y = y;
    this->size = size;
}

Rect::Rect(const Vec2 &origin, float w, float h)
{
    this->origin = origin;
    size.w = w;
    size.h = h;
}

Rect::~Rect()
{
}

Rect &Rect::operator=(const Rect &rect)
{
    origin = rect.origin;
    size = rect.size;
    return *this;
}

Rect &Rect::operator+(const Rect &rect)
{
    origin += rect.origin;
    size += rect.size;
    return *this;
}

Rect &Rect::operator-(const Rect &rect)
{
    origin -= rect.origin;
    size -= rect.size;
    return *this;
}

Rect &Rect::operator*(const Rect &rect)
{
    origin *= rect.origin;
    size *= rect.size;
    return *this;
}

Rect &Rect::operator/(const Rect &rect)
{
    origin /= rect.origin;
    size /= rect.size;
    return *this;
}
Rect &Rect::scale(float x, float y)
{
    size.w *= x;
    size.h *= y;
    return *this;
}
Rect &Rect::scale(const Vec2 &scale)
{
    size.w *= scale.x;
    size.h *= scale.y;
    return *this;
}
SDL_Rect Rect::asSDL_Rect()
{
    SDL_Rect rect = {(int)origin.x,
                     (int)origin.y,
                     size.w,
                     size.h};
    return rect;
}
