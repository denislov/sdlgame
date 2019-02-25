#pragma once
#include <vector>
#include "Object.h"

class AutoReleasePool
{
private:
	std::vector<Object *> _objectPool;
public:
	AutoReleasePool();

	~AutoReleasePool();

	void addObject(Object*object);

	void removeObject(Object*object);

	bool checkIsAvailableForId(unsigned int id);

	std::string getObjectNameById(unsigned int id) const;
	void clear();
};

