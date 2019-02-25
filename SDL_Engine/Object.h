#pragma once
#define TZ_DEBUG
#include "SETool.h"
class Object;
class AutoReleasePool;

class Clonealbe
{
  public:
	virtual Object *clone();
	virtual ~Clonealbe();
};

class Object : public Clonealbe
{
  protected:
	unsigned int _uniqueID;
	unsigned int _mRefrence;
	bool _bManaged;
	std::string _name;

  public:
	Object();
	virtual ~Object();
	CREATE_FUN(Object);
	virtual bool init();
	void retain();
	void release();
	void autoRelease();
	void setName(const std::string &name);
	std::string getName() const;
	unsigned int getReferenceCount();
	unsigned int getObjectId();
	friend class AutoReleasePool;
};
