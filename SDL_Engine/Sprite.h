#pragma once
#include "Node.h"
#include "Texture.h"
#include "Rect.h"
#include <string>
class Sprite : public Node
{
  Texture *_texture;
  std::string _key;

  Rect _rect;
  Size _originalSize;

public:
  Sprite();
  ~Sprite();
  CREATE_FUN(Sprite);
  bool init() override;
  void render() override;
  bool load(std::string filepath);
  Sprite *clone() override;

private:
  bool loadWithFile(std::string filepath);
};