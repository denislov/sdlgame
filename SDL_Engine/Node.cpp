#include "Node.h"
#include "Director.h"
#include <algorithm>
Node::Node() : _anchor(0, 0),
			   _originPoint(0, 0),
			   _localZOrder(0),
			   _isSorted(false),
			   _running(false),
			   _contentSize(0, 0),
			   _parent(nullptr),
			   _visible(true),
			   _scaleX(1.f),
			   _scaleY(1.f),
			   _rotation(0.f)
{
	_eventDispather = TheDirector::getInstance()->getEventDispather();
	_eventDispather->retain();
	_name = "Node";
}

Node::~Node()
{
	_eventDispather->removeEventListenerForNode(this);
	_eventDispather->release();
	removeChildren();
}

void Node::visit()
{
	if (_visible)
	{
		this->render();
		sortChildren();
		for (auto it : _children)
			it->visit();
	}
}

bool Node::init()
{
	return true;
}
void Node::render()
{
}
void Node::addChild(Node *child)
{
	addChild(child, child->_localZOrder);
}
void Node::addChild(Node *child, int localZOrder, int tag)
{
	if (child && child->_parent == nullptr)
	{
		_children.push_back(child);
		child->retain();
		child->_localZOrder = localZOrder;
		child->_tag = tag;
		_isSorted = false;
		child->_contentSize = _contentSize;
		child->setParent(this);
		if (_running)
			child->onEnter();
	}
}
void Node::setContentSize(const Size &size)
{
	_contentSize = size;
}

Size Node::getContentSize()
{
	return _contentSize;
}
void Node::onEnter()
{
	for (auto it : _children)
		it->onEnter();
	_running = true;
	resume();
}
void Node::onExit()
{
	for (auto it : _children)
		it->onExit();
	_running = false;
	pause();
}
void Node::resume()
{
	_eventDispather->resumeEventListenerForNode(this);
}
void Node::pause()
{
	_eventDispather->pauseEventListenerForNode(this);
}
int Node::getLocalZOrder() const
{
	return _localZOrder;
}
void Node::setLocalZOrder(int localZOrder)
{
	_localZOrder = localZOrder;
}

void Node::sortChildren()
{
	if (!_isSorted)
	{
		std::sort(std::begin(_children), std::end(_children), [](Node *n1, Node *n2) -> bool {
			return n1->_localZOrder < n2->_localZOrder;
		});
	}
	_isSorted = true;
}

void Node::setParent(Node *parent)
{
	if (_parent)
	{
		this->retain();
		_parent->removeChild(this);
	}
	_parent = parent;
	_parent->addChild(this);
}
Node *Node::getParent() const
{
	return _parent;
}

void Node::removeChild(Node *child)
{
	if (child)
	{
		for (auto iter = _children.begin(); iter != _children.end();)
		{
			auto temp = *iter;
			if (temp == child)
			{
				_children.erase(iter);
				child->_parent = nullptr;
				child->onExit();
				child->release();
				return;
			}
			iter++;
		}
	}
}
void Node::removeChildren()
{
	for (auto it = _children.begin(); it != _children.end();)
	{
		auto temp = *it;
		temp->onExit();
		temp->release();
		it = _children.erase(it);
	}
}
Vec2 Node::getWorldPosition()
{
	Vec2 point(_position);
	Vec2 parentAnthorPoint;
	Size parentSize;
	for (auto node = _parent; node != nullptr; node = node->_parent)
	{
		parentAnthorPoint = node->_anchor;
		parentSize = node->_contentSize;
		point += node->_position - Vec2(parentAnthorPoint.x * parentSize.w, parentAnthorPoint.y * parentSize.h);
	}
	point -= Vec2(_anchor.x * _contentSize.w, _anchor.y * _contentSize.h);
	return point;
}
Vec2 Node::getWorldScale()
{
	Vec2 scale(_scaleX, _scaleY);
	for (auto node = _parent; node != nullptr; node = node->_parent)
	{
		scale.x *= node->_scaleX;
		scale.y *= node->_scaleY;
	}
	return scale;
}

float Node::getScaleX() const
{
	return _scaleX;
}
float Node::getScaleY() const
{
	return _scaleY;
}
Vec2 Node::getScale() const
{
	return Vec2(_scaleX, _scaleY);
}
void Node::setScaleX(float x)
{
	_scaleX = x;
}
void Node::setScaleY(float y)
{
	_scaleY = y;
}
void Node::setScale(float x, float y)
{
	_scaleX = x;
	_scaleY = y;
}

void Node::setPosition(Vec2 pos)
{
	_position = pos;
}
void Node::setPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;
}
Vec2 Node::getPosition() const
{
	return _position;
}

void Node::addEventListener(EventListener *listener)
{
	_eventDispather->addEventListener(this, listener);
}
void Node::setAnchorPoint(Vec2 point)
{
	_anchor = point;
}
Vec2 Node::getAnchorPoint() const
{
	return _anchor;
}
float Node::getRotation() const
{
	return _rotation;
}
void Node::setRotation(float rotation)
{
	_rotation = rotation;
}