#if !defined(_COLOR_H)
#define _COLOR_H

#define RGB(r, g, b) (((r) << 16) | ((g) << 8) | (b))
#define RGBA(r, g, b, a) (((r) << 16) | ((g) << 8) | (b) | ((a) << 24))
#define ARGB(a, r, g, b) (((r) << 16) | ((g) << 8) | (b) | ((a) << 24))
#define ACOLOR(a, color) (((color)&0xFFFFFF) | ((a) << 24))
#define COLORA(color, a) (((color)&0xFFFFFF) | ((a) << 24))
#define GET_R(c) (((c) >> 16) & 0xFF)
#define GET_G(c) (((c) >> 8) & 0xFF)
#define GET_B(c) (((c)) & 0xFF)
#define GET_A(c) (((c) >> 24) & 0xFF)
#define GRAY(gray) (((gray) << 16) | ((gray) << 8) | (gray))
#define GRAYA(gray, a) (((gray) << 16) | ((gray) << 8) | (gray) | ((a) << 24))
#define AGRAY(a, gray) (((gray) << 16) | ((gray) << 8) | (gray) | ((a) << 24))

#include <SDL2/SDL.h>

class Color
{
  public:
    /* data */
    enum SDLColor
    {
        BLACK = 0,
        BLUE = RGBA(0, 0, 0xA8, 0xff),
        GREEN = RGBA(0, 0xA8, 0, 0xff),
        CYAN = RGBA(0, 0xA8, 0xA8, 0xff),
        RED = RGBA(0xA8, 0, 0, 0xff),
        MAGENTA = RGBA(0xA8, 0, 0xA8, 0xff),
        BROWN = RGBA(0xA8, 0xA8, 0, 0xff),
        LIGHTGRAY = RGBA(0xA8, 0xA8, 0xA8, 0xff),
        DARKGRAY = RGBA(0x54, 0x54, 0x54, 0xff),
        LIGHTBLUE = RGBA(0x54, 0x54, 0xFC, 0xff),
        LIGHTGREEN = RGBA(0x54, 0xFC, 0x54, 0xff),
        LIGHTCYAN = RGBA(0x54, 0xFC, 0xFC, 0xff),
        LIGHTRED = RGBA(0xFC, 0x54, 0x54, 0xff),
        LIGHTMAGENTA = RGBA(0xFC, 0x54, 0xFC, 0xff),
        YELLOW = RGBA(0xFC, 0xFC, 0x54, 0xff),
        WHITE = RGBA(0xFC, 0xFC, 0xFC, 0xff),

    };

  public:
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

  public:
    Color(Uint8 R = 0xFC, Uint8 G = 0xFC, Uint8 B = 0xFC, Uint8 A = 0xFC) : r(R),
                                                                            g(G),
                                                                            b(B),
                                                                            a(A)
    {
    }
    Color(SDLColor color) : r(GET_R(color)), g(GET_G(color)),
                            b(GET_B(color)),
                            a(GET_A(color))
    {
    }
    Color(Uint32 color) : r(GET_R(color)),
                          g(GET_G(color)),
                          b(GET_B(color)),
                          a(GET_A(color))
    {
    }
    Color(const SDL_Color color) : r(color.r),
                             g(color.g),
                             b(color.b),
                             a(color.a)
    {
    }

    //重载运算符
    Color operator*(Uint8 d)
    {
        return Color(r * d, g * d, b * d, a * d);
    }
    Color operator+(const Color &color)
    {
        return Color(r + color.r, g + color.g, b + color.b, a + color.a);
    }
    Color operator-(const Color &color)
    {
        return Color(r - color.r, g - color.g, b - color.b);
    }
    
    bool operator==(const Color &other)
    {
        if (this == &other)
            return true;
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }
    bool equals(const Color &other)
    {
        if (this == &other)
            return true;
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }
    bool operator!=(const Color &other)
    {
        if (this == &other)
            return false;
        return r != other.r || g != other.g || b != other.b || a != other.a;
    }
    SDL_Color getSDL_Color() const
    {
        SDL_Color color = {r, g, b, a};
        return color;
    }

    ~Color()
    {
    }
};
#endif // _COLOR_H
