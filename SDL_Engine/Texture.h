#pragma once
#include "Object.h"
#include "SDL_image.h"
#include <string>
class Texture : public Object
{
  public:
	Texture();
	~Texture();
	static Texture *create(SDL_Texture *pTex);
	static Texture *create(std::string filepath);
	bool init(SDL_Texture *pTex);
	bool init(std::string filepath);
	SDL_Texture *getSDLTexture();
	void queryTexture(Uint32 *format, int *access, int *w, int *h);
private:
	SDL_Texture *_texture;
};
