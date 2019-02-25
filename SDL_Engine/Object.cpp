#include "Object.h"
#include <iostream>
#include "PoolManager.h"

Object *Clonealbe::clone()
{
	return nullptr;
}
Clonealbe::~Clonealbe() {}

Object::Object() : _uniqueID(0), _bManaged(false), _name("")
{
	static int m_objectCount = 0;
	m_objectCount++;
	_mRefrence = 1;
	_uniqueID = m_objectCount;
}

Object::~Object()
{
	if (!_name.empty())
		printf("%s is released ,its id is %d\n", _name.c_str(), _uniqueID);
}

bool Object::init()
{
	return true;
}

void Object::retain()
{
	_mRefrence++;
}

void Object::release()
{
	_mRefrence--;
	if (_mRefrence == 0)
		delete this;
}

void Object::autoRelease()
{
	if (!_bManaged)
	{
		ThePoolManager::getInstance()->addObject(this);
		_bManaged = true;
	}
}
unsigned int Object::getReferenceCount()
{
	return _mRefrence;
}
unsigned int Object::getObjectId()
{
	return _uniqueID;
}
void Object::setName(const std::string &name) { _name = name; }
std::string Object::getName() const
{
	return _name;
}
