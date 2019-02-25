#include "Window.h"

Window::Window() : _window(nullptr),
				   _width(0),
				   _height(0),
				   _position(0, 0)
{
	_name = "Window";
}

Window::~Window()
{
	SDL_DestroyWindow(_window);

	_window = nullptr;
}

Window *Window::create(const char *title, int x, int y, int width, int height, Uint32 flags)
{
	auto _win = new Window();
	if (_win && _win->init(title, x, y, width, height, flags))
	{
		_win->autoRelease();
		return _win;
	}
	delete _win;
	_win = nullptr;
	return _win;
}

bool Window::init(const char *title, int x, int y, int width, int height, Uint32 flags)
{
	_window = SDL_CreateWindow(title, x, y, width, height, flags);
	if (_window == nullptr)
	{
		printf("create window failed: %s", SDL_GetError());
		return false;
	}
	_position.x = x;
	_position.y = y;
	_width = width;
	_height = height;
	return true;
}

Size Window::getWindowSize()
{
	return Size(_width, _height);
}
SDL_Window *Window::getSDLWindow()
{
	return _window;
}