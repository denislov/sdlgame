
#if !defined(_WINDOW_H)
#define _WINDOW_H

#include "Object.h"
#include "SDL2/SDL.h"
#include "Size.h"
#include "Vec2.h"
class Renderer;

class Window : public Object
{
  public:
	friend class Renderer;
	Window();
	~Window();
	static Window *create(const char *title, int x, int y, int width, int height, Uint32 flags);
	bool init(const char *title, int x, int y, int width, int height, Uint32 flags);
	Size getWindowSize();
	SDL_Window *getSDLWindow();

  private:
	SDL_Window *_window;
	Vec2 _position;
	int _width;
	int _height;
};

#endif // _WINDOW_H

