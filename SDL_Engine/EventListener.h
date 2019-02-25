#ifndef _SDL_EventListener_H
#define _SDL_EventListener_H
#include <functional>
#include "Object.h"
#include "Node.h"
class EventListener : public Object
{
  protected:
    //是否注册，只能被注册一次
    bool _bRegistered;
    //是否暂停 默认为true
    bool _paused;
    //优先级，越小优先级越高，最小为0，添加容错性
    int _priority;

    //绑定每个对象的唯一id
    Node *_bindNode;
    //是否吞并事件
    bool _swallow;
    std::string _listenerID;

  protected:
    EventListener() : _bRegistered(false),
                      _paused(true),
                      _swallow(false),
                      _priority(0),
                      _listenerID(""),
                      _bindNode(nullptr)
    {
        _name = "EventListener";
    }

  public:
    bool init(const std::string &id)
    {
        _listenerID = id;
        return true;
    }
    virtual ~EventListener() {}
    virtual bool checkAvailable() const = 0;

    virtual EventListener *clone() = 0;

  public:
    void setRegistered(bool registered)
    {
        _bRegistered = registered;
    }
    bool isRegistered() const
    {
        return _bRegistered;
    }
    int getPriority()
    {
        return _priority;
    }
    void setPriority(int priority)
    {
        if (_priority != priority)
        {
            _priority = priority;
        }
    }
    void setBindNode(Node *node)
    {
        _bindNode = node;
    }
    Node* getBindNode() const
    {
        return _bindNode;
    }
    bool isPaused() const
    {
        return _paused;
    }
    void setPaused(bool pause)
    {
        _paused = pause;
    }
    void setSwallowTouches(bool swallow)
    {
        _swallow = swallow;
    }
    bool isSwallowTouches()
    {
        return _swallow;
    }
    std::string getListenerID() const
    {
        return _listenerID;
    }
};
#endif