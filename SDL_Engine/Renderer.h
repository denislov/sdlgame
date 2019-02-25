#pragma once
#include "Object.h"
#include "SDL2/SDL.h"
#include "Window.h"
#include "Color.h"
#include "Texture.h"
#include <string>
class Renderer :
	public Object
{
public:
	Renderer();
	~Renderer();
	static Renderer*create(Window*window, int index, Uint32 flags);
	bool init(Window*window, int index, Uint32 flags);
	void renderClear();
	void renderPresent();
	SDL_Renderer *getSDLRenderer();
	void setBgColor(Color color);
	Texture *createTexture(const std::string &filepath);

  private:
	SDL_Renderer *_renderer;
	Color _bgColor;
};

