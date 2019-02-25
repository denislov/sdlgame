#ifndef _NODE_H
#define _NODE_H
#include <vector>
#include "Object.h"
#include "Rect.h"
class InputHandler;
class EventListener;
class Node : public Object
{
  public:
	Node();
	virtual ~Node();
	CREATE_FUN(Node);
	virtual bool init();
	virtual void visit();
	virtual void render();
	void addChild(Node *child);
	void addChild(Node *child, int localZOrder, int tag = -1);
	Size getContentSize();
	void setContentSize(const Size &size);
	virtual void onEnter();
	virtual void onExit();
	int getLocalZOrder() const;
	void setLocalZOrder(int localZOrder);
	void sortChildren();

	void resume();
	void pause();
	void setParent(Node *parent);
	Node *getParent() const;
	void removeChild(Node *child);
	void removeChildren();
	Vec2 getWorldPosition();
	Vec2 getWorldScale();
	float getScaleX() const;
	float getScaleY() const;
	Vec2 getScale() const;
	void setScaleX(float x);
	void setScaleY(float y);
	void setScale(float x, float y);
	void setPosition(Vec2 pos);
	void setPosition(float x, float y);
	Vec2 getPosition() const;
	void addEventListener(EventListener *listener);
	void setAnchorPoint(Vec2 point);
	Vec2 getAnchorPoint() const;
	float getRotation()const;
	void setRotation(float rotation);

  protected:
	bool _isSorted;
	bool _visible;
	bool _running;
	int _tag;
	float _scaleX;
	float _scaleY;
	//旋转
	float _rotation;
	//坐标
	Size _contentSize;
	Vec2 _anchor;
	Vec2 _originPoint;
	Vec2 _position;

	Node *_parent;
	int _localZOrder;
	std::vector<Node *> _children;

	InputHandler *_eventDispather;
};
#endif