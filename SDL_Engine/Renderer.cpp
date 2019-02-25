#include "Renderer.h"

Renderer::Renderer() : _renderer(nullptr),
					   _bgColor(Color::WHITE)
{
	_name = "Renderer";
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(_renderer);
	_renderer = nullptr;
}

Renderer *Renderer::create(Window *window, int index, Uint32 flags)
{
	auto renderer = new Renderer();
	if (renderer && renderer->init(window, index, flags))
	{
		renderer->autoRelease();
	}
	else
	{
		delete renderer;
		renderer = nullptr;
	}
	return renderer;
}

bool Renderer::init(Window *window, int index, Uint32 flags)
{
	_renderer = SDL_CreateRenderer(window->_window, index, flags);
	if (_renderer == nullptr)
	{
		printf("create window failed: %s", SDL_GetError());
		return false;
	}
	return true;
}

void Renderer::renderClear()
{
	SDL_SetRenderDrawColor(_renderer, _bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a);
	SDL_RenderClear(_renderer);
}

void Renderer::renderPresent()
{
	SDL_RenderPresent(_renderer);
}
SDL_Renderer *Renderer::getSDLRenderer()
{
	return _renderer;
}

void Renderer::setBgColor(Color color)
{
	_bgColor = color;
}
Texture *Renderer::createTexture(const std::string &filepath)
{
	SDL_Texture *tex = IMG_LoadTexture(_renderer, filepath.c_str());
	return Texture::create(tex);
}
