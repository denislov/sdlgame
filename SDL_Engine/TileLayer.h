
#if !defined(_TILELAYER_H)
#define _TILELAYER_H
#include "Tiledset.h"
#include "Layer.h"
#include "Texture.h"
#include <string>
class TileLayer : public Layer
{
  private:
    /* data */
    std::vector<Tiledset *> _tilesets;
    int *_data;
    std::vector<Texture*> _image;
    void parseTileLayers(pugi::xml_node *layerRoot);
    void parseTilesets(pugi::xml_node *layerRoot);
    Tiledset *getTilesetByID(int id);
    int _width;
    int _height;
  public:
    TileLayer(/* args */);
    ~TileLayer();
    CREATE_FUN(TileLayer);
    bool init();
    bool loadMapWithFile(const std::string &filename);
    void render();
    
    void drawTile(int id,Tiledset *tile,int currentFrame,int currentRow);
};

#endif // _TILELAYER_H
