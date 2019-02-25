#include "TextureCache.h"

#include "Director.h"

#include "FileUtils.h"
TextureCache::TextureCache(/* args */)
{
    _name = "TextureCache";
}

TextureCache::~TextureCache()
{
    removeAllTextures();
}

Texture *TextureCache::addImage(const std::string &filename)
{
    return addImage(filename, filename);
}
Texture *TextureCache::addImage(const std::string &filename, const std::string &key)
{
    auto iter = _textures.find(key);
    if (iter != _textures.end())
    {
        return iter->second;
    }
    auto renderer = TheDirector::getInstance()->getRenderer();

    auto filepath = TheFileUtils::getInstance()->fullPathForFileName(filename);

    if (filepath.empty())
        return nullptr;
    auto texture = renderer->createTexture(filepath);
    texture->retain();
    _textures.insert(std::make_pair(key, texture));

    return texture;
}
Texture *TextureCache::getTextureForKey(const std::string &key)
{
    auto iter = _textures.find(key);
    if (iter != _textures.end())
        return iter->second;
    return nullptr;
}
void TextureCache::removeUnusedTextures()
{
    //遍历，找到引用为1的Texture，若有，则删除
    for (auto iter = _textures.begin(); iter != _textures.end();)
    {
        auto texture = iter->second;

        if (texture->getReferenceCount() == 1)
        {
            iter = _textures.erase(iter);
            texture->release();
        }
        else
            ++iter;
    }
}
void TextureCache::removeTextureForKey(const std::string &key)
{
    auto iter = _textures.find(key);
    if (iter != _textures.end())
    {
        auto texture = iter->second;
        _textures.erase(iter);
        texture->release();
    }
}
void TextureCache::removeAllTextures()
{
    for (auto iter = _textures.begin(); iter != _textures.end();)
    {
        auto texture = iter->second;

        iter = _textures.erase(iter);
        texture->release();
    }
}