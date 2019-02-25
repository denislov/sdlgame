//
// Created by tuanzi on 18-12-11.
//

#include "Size.h"

Size::Size(int w, int h)
{
    this->w = w;
    this->h = h;
}

Size::Size(const Size &point)
{
    this->w = point.w;
    this->h = point.h;
}

Size &Size::operator=(const Size &point)
{
    this->w = point.w;
    this->h = point.h;
    return *this;
}

Size &Size::operator+(const Size &point)
{
    this->w += point.w;
    this->h += point.h;
    return *this;
}

Size &Size::operator-(const Size &point)
{
    this->w -= point.w;
    this->h -= point.h;
    return *this;
}

Size &Size::operator*(const Size &point)
{
    this->w *= point.w;
    this->h *= point.h;
    return *this;
}

Size &Size::operator/(const Size &point)
{
    this->w /= point.w;
    this->h /= point.h;
    return *this;
}

Size &operator+=(Size &v1, const Size &v2)
{
    v1.w += v2.w;
    v1.h += v2.h;
    return v1;
}
Size &operator-=(Size &v1, const Size &v2)
{
    v1.w -= v2.w;
    v1.h -= v2.h;
    return v1;
}
Size &operator*=(Size &v1, const Size &v2)
{
    v1.w *= v2.w;
    v1.h *= v2.h;
    return v1;
}
Size &operator/=(Size &v1, const Size &v2)
{
    v1.w /= v2.w;
    v1.h /= v2.h;
    return v1;
}

Size::~Size()
{
}

SDL_Rect Size::asSDL_Rect()
{
    return SDL_Rect();
}
