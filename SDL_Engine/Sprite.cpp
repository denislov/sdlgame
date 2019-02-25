#include "Sprite.h"
#include "Director.h"
Sprite::Sprite() : Node(), _texture(nullptr)
{
    _name = "Sprite";
}
Sprite::~Sprite()
{
    _texture->release();
}

void Sprite::render()
{
    Vec2 point(_position);
    Vec2 parentAnthorPoint;
    double angle = _rotation;
    Size parentSize;
    Vec2 scale(_scaleX, _scaleY);
    for (auto node = _parent; node != nullptr; node = node->getParent())
    {
        parentAnthorPoint = node->getAnchorPoint();
        parentSize = node->getContentSize();
        point += node->getPosition() - Vec2(parentAnthorPoint.x * parentSize.w, parentAnthorPoint.y * parentSize.h);
        scale.x *= node->getScaleX();
        scale.y *= node->getScaleY();
        angle += node->getRotation();
    }

    point -= Vec2(_anchor.x * _originalSize.w * scale.x, _anchor.y * _originalSize.h * scale.y);

    SDL_Rect srcRect = _rect.asSDL_Rect();
    SDL_Rect destRect = {
        static_cast<int>(point.x),
        static_cast<int>(point.y),
        static_cast<int>(_rect.size.w * scale.x),
        static_cast<int>(_rect.size.h * scale.y),
    };

    SDL_Point center = {static_cast<int>(destRect.x + _anchor.x * destRect.w),
                        static_cast<int>(destRect.y + _anchor.y * destRect.h)};

    auto render = TheDirector::getInstance()->getRenderer()->getSDLRenderer();
    SDL_RenderCopyEx(render, _texture->getSDLTexture(), &srcRect, &destRect, angle, &center, SDL_FLIP_NONE);
}

bool Sprite::load(std::string filepath)
{
    return loadWithFile(filepath);
}
bool Sprite::loadWithFile(std::string filepath)
{
    auto texture = TheDirector::getInstance()->getTextureCache()->addImage(filepath);

    if (texture)
    {
        int w = 0, h = 0;
        texture->queryTexture(nullptr, nullptr, &w, &h);
        _rect.size.w = w;
        _rect.size.h = h;
        _originalSize = _rect.size;
        _texture = texture;
        _key = filepath;
        setContentSize(_originalSize);
        setAnchorPoint(Vec2(0.5f, 0.5f));
        texture->retain();
        return true;
    }

    return false;
}

bool Sprite::init()
{
    return true;
}
Sprite *Sprite::clone()
{
    auto sprite = Sprite::create();
    sprite->_texture = this->_texture;
    sprite->_texture->retain();
    sprite->_position = this->_position;
    sprite->_key = this->_key;
    sprite->_rect = this->_rect;
    sprite->_originalSize = this->_originalSize;
    sprite->setContentSize(this->_originalSize);
    sprite->setAnchorPoint(this->_anchor);
    sprite->_scaleX = this->_scaleX;
    sprite->_scaleY = this->_scaleY;
    sprite->_rotation = this->_rotation;
    return sprite;
}