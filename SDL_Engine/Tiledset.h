
#if !defined(_TILEDSET_H)
#define _TILEDSET_H

#include "pugixml/pugixml.hpp"
#include "Object.h"
#include <string>
class Tiledset : public Object
{
  public:
    /* data */
    int firstGrid;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int tileCount;
    int columns;
    int width;
    int height;
    std::string name;
    std::string source;

  public:
    Tiledset(/* args */);
    ~Tiledset();
    static Tiledset *create(pugi::xml_node *root);
    bool init(pugi::xml_node *root);
    
};

#endif // _TILEDSET_H
