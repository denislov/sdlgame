#include "AutoReleasePool.h"

AutoReleasePool::AutoReleasePool()
{
}

AutoReleasePool::~AutoReleasePool()
{
	printf("Objects pool deleted\n");
}

void AutoReleasePool::addObject(Object *object)
{
	_objectPool.push_back(object);
}

void AutoReleasePool::removeObject(Object *object)
{
	for (auto it = _objectPool.begin(); it != _objectPool.end(); it++)
	{
		if (*it == object)
		{
			_objectPool.erase(it);
			object->_bManaged = false;
			return;
		}
	}
}

void AutoReleasePool::clear()
{
	for (auto it = _objectPool.begin(); it != _objectPool.end();)
	{
		(*it)->_bManaged = false;
		(*it)->release();
		it = _objectPool.erase(it);
	}
}
bool AutoReleasePool::checkIsAvailableForId(unsigned int id)
{
	for (auto it = _objectPool.begin(); it != _objectPool.end(); it++)
	{
		if ((*it)->getObjectId() == id)
			return true;
	}
	return false;
}
std::string AutoReleasePool::getObjectNameById(unsigned int id) const
{

	for (auto it = _objectPool.begin(); it != _objectPool.end(); it++)
	{
		if ((*it)->getObjectId() == id)
			return (*it)->getName();
	}
	return "unsuccess";
}
