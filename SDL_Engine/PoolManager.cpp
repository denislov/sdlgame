#include "PoolManager.h"
#include "SETool.h"

PoolManager *PoolManager::_pInstance = nullptr;

PoolManager::PoolManager()
{
	_pool = new AutoReleasePool();
}

PoolManager::~PoolManager()
{
	printf("Pool manager deleted\n");
}

PoolManager *PoolManager::getInstance()
{
	if (_pInstance == nullptr)
		_pInstance = new PoolManager();
	return _pInstance;
}

void PoolManager::addObject(Object *object)
{
	_pool->addObject(object);
}

void PoolManager::removeObject(Object *object)
{
	_pool->removeObject(object);
}

AutoReleasePool *PoolManager::getCurrentObjectPool()
{
	return _pool;
}

void PoolManager::purge()
{
	TZ_SAFE_DELETE(_pool);
	delete this;
}