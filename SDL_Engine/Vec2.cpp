//
// Created by tuanzi on 18-12-11.
//

#include "Vec2.h"

Vec2::Vec2(float x, float y)
{
    this->x =x;
    this->y =y;

}

Vec2::Vec2(const Vec2 &Vec2)
{
this->x = Vec2.x;
this->y = Vec2.y;
}

Vec2 &Vec2::operator=(const Vec2 &Vec2)
{
    this->x = Vec2.x;
    this->y = Vec2.y;
    return *this;
}

Vec2 &Vec2::operator+(const Vec2 &Vec2)
{
    this->x += Vec2.x;
    this->y += Vec2.y;
    return *this;
}

Vec2 &Vec2::operator-(const Vec2 &Vec2)
{
    this->x -= Vec2.x;
    this->y -= Vec2.y;
    return *this;
}

Vec2 &Vec2::operator*(const Vec2 &Vec2)
{
    this->x *= Vec2.x;
    this->y *= Vec2.y;
    return *this;
}

Vec2 &Vec2::operator/(const Vec2 &Vec2)
{
    this->x /= Vec2.x;
    this->y /= Vec2.y;
    return *this;
}


Vec2 &operator+=( Vec2 &v1, const Vec2 &v2)
{
    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

Vec2 &operator-=( Vec2 &v1, const Vec2 &v2)
{
    v1.x -= v2.x;
    v1.y -= v2.y;
    return v1;
}

Vec2 &operator*=( Vec2 &v1, const Vec2 &v2)
{
    v1.x *= v2.x;
    v1.y *= v2.y;
    return v1;
}

Vec2 &operator/=( Vec2 &v1, const Vec2 &v2)
{
    v1.x /= v2.x;
    v1.y /= v2.y;
    return v1;
}

Vec2::~Vec2()
{

}

SDL_Point Vec2::asSDL_Point()
{
    SDL_Point point = {(int)this->x,(int)this->y};
    return point;
}
