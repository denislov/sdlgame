#pragma once
#include "Object.h"
#include "AutoReleasePool.h"

class PoolManager
{
private:
	PoolManager();
	~PoolManager();
	static PoolManager *_pInstance;
	AutoReleasePool *_pool;
public:
	static PoolManager *getInstance();

	void addObject(Object *object);

	void removeObject(Object *object);

	AutoReleasePool *getCurrentObjectPool();

	void purge();
};

typedef PoolManager ThePoolManager;
