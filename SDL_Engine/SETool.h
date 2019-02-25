#pragma once
#include <cassert>
#include <cstdio>
#include <string>
#include <functional>

#define LOG(format, ...)                                 \
    do                                                   \
    {                                                    \
        printf("FILE:%s,LINE:%d\n", __FILE__, __LINE__); \
        printf((format), ##__VA_ARGS__);                 \
    } while (0)

#define TZASSERT(cond, msg)                \
    if (!cond)                             \
    {                                      \
        printf("Assert failed : %s", msg); \
        assert(cond);                      \
    }

#define CREATE_FUN(__TYPE__)         \
    static __TYPE__ *create()        \
    {                                \
        auto *pRet = new __TYPE__(); \
        if (pRet && pRet->init())    \
        {                            \
            pRet->autoRelease();     \
            return pRet;             \
        }                            \
        delete pRet;                 \
        pRet = nullptr;              \
        return pRet;                 \
    }

#define TZ_SAFE_DELETE(p) \
    if (p)                \
    {                     \
        delete p;         \
        p = nullptr;      \
    }

#define SDL_CALLBACK_1(__selector__, __target__, ...) std::bind(&__selector__, __target__, std::placeholders::_1, ##__VA_ARGS__)
#define SDL_CALLBACK_2(__selector__, __target__, ...) std::bind(&__selector__, __target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
