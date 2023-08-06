#include "Killable.hpp"

using namespace components;

Killable::Killable(std::string strName, float fFrameInterval) : Component(strName, ComponentType::SCRIPT) {
    this->fFrameInterval = fFrameInterval;
    this->fTicks = 0.0f;
    this->bKilled = false;
}

void Killable::perform() {
    if(this->bKilled) {
        this->fTicks += this->tDeltaTime.asSeconds();
        
        if (this->fTicks > this->fFrameInterval) {
            this->fTicks = 0.0f;
            this->getOwner()->incrementFrame();
            if (this->getOwner()->getCurrentFrame() >= this->getOwner()->getFrameSize() - 1) {
                PoolableObject* pPoolableObject = (PoolableObject*)this->getOwner();
                ObjectPoolManager::getInstance()->getPool(pPoolableObject->getTag())->releasePoolable(pPoolableObject);
                this->bKilled = false;
            }
        }
    }
}

bool Killable::isKilled() {
    return this->bKilled;
}

void Killable::setKilled(bool bKilled) {
    this->bKilled = bKilled;
}
