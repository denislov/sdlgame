#include "Texture.h"
#include "Director.h"
#include "Window.h"
Texture::Texture()
{
	_name = "Texture";
}

Texture::~Texture()
{
	SDL_DestroyTexture(_texture);
	_texture = nullptr;
}

Texture *Texture::create(SDL_Texture *pTex)
{
	auto texture = new Texture();
	if (texture && texture->init(pTex))
	{
		texture->autoRelease();
		return texture;
	}
	else
	{
		delete texture;
		texture = nullptr;
	}
	return texture;
}

bool Texture::init(SDL_Texture *pTex)
{
	_texture = pTex;
	return true;
}
Texture *Texture::create(std::string filepath)
{
	auto texture = new Texture();
	if (texture && texture->init(filepath))
	{
		texture->autoRelease();
		return texture;
	}
	else
	{
		delete texture;
		texture = nullptr;
	}
	return texture;
}
bool Texture::init(std::string filepath)
{
	_texture = IMG_LoadTexture(TheDirector::getInstance()->getRenderer()->getSDLRenderer(),filepath.c_str());
	if (_texture == nullptr)
		return false;
	return true;
}
SDL_Texture *Texture::getSDLTexture() { return _texture; }
void Texture::queryTexture(Uint32 *format, int *access, int *w, int *h)
{
	if (_texture)
		SDL_QueryTexture(_texture, format, access, w, h);
}