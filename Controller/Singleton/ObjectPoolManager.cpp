#include "ObjectPoolManager.hpp"

using namespace controllers;

void ObjectPoolManager::registerObjectPool(GameObjectPool* pPool) {
    this->mapObjectPool[pPool->getTag()] = pPool;
}

void ObjectPoolManager::unregisterObjectPool(GameObjectPool* pPool) {
    this->mapObjectPool.erase(pPool->getTag());
}

GameObjectPool* ObjectPoolManager::getPool(PoolTag ETag) {
    return this->mapObjectPool[ETag];
}

ObjectPoolManager* ObjectPoolManager::P_SHARED_INSTANCE = NULL;
ObjectPoolManager::ObjectPoolManager() {}
ObjectPoolManager::ObjectPoolManager(const ObjectPoolManager&) {}

ObjectPoolManager* ObjectPoolManager::getInstance() {
    if(P_SHARED_INSTANCE == NULL)
        P_SHARED_INSTANCE = new ObjectPoolManager();

    return P_SHARED_INSTANCE;
}
