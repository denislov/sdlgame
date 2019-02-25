#include "TileLayer.h"
#include "FileUtils.h"
#include "base64.h"
#include "zlib.h"
#include "iostream"
#include "Director.h"
using namespace pugi;

TileLayer::TileLayer(/* args */)
{
}

TileLayer::~TileLayer()
{
    delete[] _data;
}
bool TileLayer::init()
{
    return true;
}
bool TileLayer::loadMapWithFile(const std::string &filename)
{
    auto filepath = TheFileUtils::getInstance()->fullPathForFileName(filename);
    xml_document doc;
    if (doc.load_file(filepath.c_str()))
    {
        xml_node mapRoot = doc.child("map");
        parseTilesets(&mapRoot);
    }
    return true;
}
void TileLayer::parseTilesets(xml_node *mapRoot)
{
    for (auto &e : mapRoot->children())
    {
        std::string name = e.name();
        if (name == "tileset")
        {
            auto tileset = Tiledset::create(&e);
            auto texture = TheDirector::getInstance()->getTextureCache()->addImage(tileset->source);
            texture->retain();
            _image.push_back(texture);
            _tilesets.push_back(tileset);
        }
        else if (name == "layer")
            parseTileLayers(&e);
    }
}
void TileLayer::parseTileLayers(xml_node *mapRoot)
{
    _name = mapRoot->attribute("name").as_string();
    _width = mapRoot->attribute("width").as_int();
    _height = mapRoot->attribute("height").as_int();
    std::string decodedIDs;
    xml_node pDataNode;
    pDataNode = mapRoot->child("data");
    //解码数据，并用string保存

    std::string t = pDataNode.child_value();
    t.erase(0, t.find_first_not_of("\n "));
    t.erase(t.find_last_not_of("\n ") + 1, t.find_last_of(" \n"));
    decodedIDs = base64_decode(t);

    //uncompress解压
    uLongf numGids = _width * _height * sizeof(int);
    std::vector<unsigned> gids(numGids);

    uncompress((Bytef *)&gids[0], &numGids, (const Bytef *)decodedIDs.c_str(), decodedIDs.size());

    _data = new int[_height * _width]{0};
    //为该二维数组赋值
    for (int rows = 0; rows < _height; rows++)
    {
        for (int cols = 0; cols < _width; cols++)
        {
            _data[rows * _width + cols] = gids[rows * _width + cols];
        }
    }
}

void TileLayer::render()
{
    for (int i = 0; i < _height; i++)
    {
        for (int j = 0; j < _width; j++)
        {
            int id = _data[i * _width + j];
            //0代表无图块
            if (id == 0)
            {
                continue;
            }
            auto tileset = getTilesetByID(id);
            if (tileset != nullptr)
                drawTile(id - 1, tileset, j, i);
        }
    }
}
Tiledset *TileLayer::getTilesetByID(int id)
{
    for (auto &tileset : _tilesets)
    {
        if (id >= tileset->firstGrid && id < (tileset->firstGrid + tileset->tileCount - 1))
            return tileset;
    }
    return nullptr;
}
void TileLayer::drawTile(int id, Tiledset *tileset, int currentFrame, int currentRow)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    int j = (id - tileset->firstGrid + 1) / tileset->columns;
    int i = (id - tileset->firstGrid + 1) - j * tileset->columns;
    srcRect.x = tileset->margin + (tileset->spacing + tileset->tileWidth) * i;
    srcRect.y = tileset->margin + (tileset->spacing + tileset->tileHeight) * j;

    srcRect.w = destRect.w = tileset->tileWidth;
    srcRect.h = destRect.h = tileset->tileHeight;

    destRect.x = currentFrame * tileset->tileWidth;
    destRect.y = currentRow * tileset->tileHeight;

    auto texture = TheDirector::getInstance()->getTextureCache()->addImage(tileset->source);
    auto render = TheDirector::getInstance()->getRenderer()->getSDLRenderer();
    SDL_RenderCopy(render, texture->getSDLTexture(), &srcRect, &destRect);
}