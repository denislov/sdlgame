
#if !defined(_TEXTURECACHE_H)
#define _TEXTURECACHE_H

#include "Texture.h"
#include <unordered_map>
#include <string>
class TextureCache : public Object
{
private:
  /* data */
  std::unordered_map<std::string, Texture *> _textures;

public:
  TextureCache(/* args */);
  ~TextureCache();

  Texture *addImage(const std::string &filename);
  Texture *addImage(const std::string &filename, const std::string &key);

  Texture *getTextureForKey(const std::string &key);

  void removeUnusedTextures();
  void removeTextureForKey(const std::string &key);
  void removeAllTextures();
};


#endif // _TEXTURECACHE_H
