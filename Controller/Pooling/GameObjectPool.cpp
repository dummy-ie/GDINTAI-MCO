#include "GameObjectPool.hpp"

using namespace controllers;

GameObjectPool::GameObjectPool(PoolTag ETag, int nPoolSize, PoolableObject* pPoolableReference, GameObject* pParent) {
    this->ETag = ETag;
    this->nPoolSize = nPoolSize;
    this->pPoolableReference = pPoolableReference;
    this->pParent = pParent;

    this->vecAvailableObject = {};
    this->vecUsedObject = {};
}

void GameObjectPool::initialize() {
    PoolableObject* pPoolableObject;
    
    for(int i = 0; i < this->nPoolSize; i++) {
        pPoolableObject = this->pPoolableReference->clone();

        if(this->pParent != NULL)
            this->pParent->attachChild(pPoolableObject);
        else
            //GameObjectManager::getInstance()->addObject(pPoolableObject);
        
        pPoolableObject->setEnabled(false);
        this->vecAvailableObject.push_back(pPoolableObject);
    }
}

PoolableObject* GameObjectPool::requestPoolable() {
    PoolableObject* pPoolableObject = NULL;

    if(this->hasAvailable(1)) {
        pPoolableObject = this->vecAvailableObject[0];
        this->vecUsedObject.push_back(pPoolableObject);
        this->vecAvailableObject.erase(this->vecAvailableObject.begin());

        this->setEnabled(pPoolableObject, true);
    }
    else
        std::cout << "[ERROR] : GameObjectPool::requestPoolable() FAILED due to no available objects." << std::endl;

    return pPoolableObject;
}

std::vector<PoolableObject*> GameObjectPool::requestPoolableBatch(int nRequestSize) {
    std::vector<PoolableObject*> vecPoolableBatch = {};

    if(this->hasAvailable(nRequestSize)) {
        for(int i = 0; i < nRequestSize; i++)
            vecPoolableBatch.push_back(this->requestPoolable());
    }
    else
        std::cout << "[ERROR] : Not enough poolable objects. REQUESTED : " << nRequestSize << " | AVAILABLE : " << this->vecAvailableObject.size() << std::endl;

    return vecPoolableBatch;
}

void GameObjectPool::releasePoolable(PoolableObject* pPoolableObject) {
    int nIndex = -1;

    for(int i = 0; i < this->vecUsedObject.size() && nIndex == -1; i++) {
        if(this->vecUsedObject[i] == pPoolableObject)
            nIndex = i;
    }

    if(nIndex != -1) {
        this->vecAvailableObject.push_back(pPoolableObject);
        this->vecUsedObject.erase(this->vecUsedObject.begin() + nIndex);
        this->setEnabled(pPoolableObject, false);
    }
}

void GameObjectPool::releasePoolableBatch(std::vector<PoolableObject*> vecPoolableObject) {
    for(int i = 0; i < vecPoolableObject.size(); i++)
        this->releasePoolable(vecPoolableObject[i]);
}

bool GameObjectPool::hasAvailable(int nRequestSize) {
    if(this->vecAvailableObject.size() >= nRequestSize)
        return true;

    return false;
}

void GameObjectPool::setEnabled(PoolableObject* pPoolableObject, bool bEnabled) {
    pPoolableObject->setEnabled(bEnabled);

    if(bEnabled)
        pPoolableObject->onActivate();
        
    else
        pPoolableObject->onRelease();
}

PoolTag GameObjectPool::getTag() {
    return this->ETag;
}
