#include "TankBulletExplode.hpp"

using namespace components;

TankBulletExplode::TankBulletExplode(std::string strName)
                     : Component(strName, ComponentType::SCRIPT) {
    this->fFrameInterval = 0.1f;
    this->fTicks = 0.0f;
}

void TankBulletExplode::perform() {
    Collider* pCollider = (Collider*)this->pOwner->findComponentByName(this->pOwner->getName() + " Collider");
    PoolableObject* pPoolableOwner = (PoolableObject*)this->pOwner;

    if(pCollider == NULL || pPoolableOwner == NULL) {
        std::cout << "[ERROR] : One or more dependencies are missing." << std::endl;
    }
    else {
        this->fTicks += this->tDeltaTime.asSeconds();

        if (this->getOwner()->getCurrentFrame() < this->getOwner()->getFrameSize() - 1) {
            if (this->fTicks > this->fFrameInterval) {
                this->fTicks = 0.0f;
                this->getOwner()->incrementFrame();
                this->getOwner()->centerSpriteOrigin();
            }
        }
        else {
            this->getOwner()->setFrame(0);
            this->getOwner()->centerSpriteOrigin();
            this->detachOwner();
            ObjectPoolManager::getInstance()->getPool(pPoolableOwner->getTag())->releasePoolable(pPoolableOwner);
        }
    }
}
