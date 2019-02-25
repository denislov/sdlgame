#include "Tiledset.h"

Tiledset::Tiledset(/* args */) : firstGrid(0),
                                 tileWidth(0),
                                 tileHeight(0),
                                 spacing(0),
                                 margin(0),
                                 tileCount(0),
                                 columns(0),
                                 width(0),
                                 height(0),
                                 name(""),
                                 source("")
{
}

Tiledset::~Tiledset()
{
}

Tiledset *Tiledset::create(pugi::xml_node *root)
{
    auto tiledset = new Tiledset();
    if (tiledset)
    {
        tiledset->autoRelease();
        tiledset->init(root);
    }
    else
    {
        delete tiledset;
        tiledset = nullptr;
    }
    return tiledset;
}
bool Tiledset::init(pugi::xml_node *root)
{
    firstGrid = root->attribute("firstgid").as_int();
    tileWidth = root->attribute("tilewidth").as_int();
    tileHeight = root->attribute("tileheight").as_int();
    spacing = root->attribute("spacing").as_int();
    margin = root->attribute("margin").as_int();
    tileCount = root->attribute("tilecount").as_int();
    columns = root->attribute("columns").as_int();
    name = root->attribute("name").as_string();
    source = root->child("image").attribute("source").as_string();
    width = root->child("image").attribute("width").as_int();
    height = root->child("image").attribute("height").as_int();
    return true;
}