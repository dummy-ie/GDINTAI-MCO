#include "TankBulletMovement.hpp"

using namespace components;

TankBulletMovement::TankBulletMovement(std::string strName)
                     : Component(strName, ComponentType::SCRIPT) {
    this->bEnabled = true;
    this->fFrameInterval = 0.01f;
    this->fTicks = 0.0f;
    this->fSpeed = 230.0f;
}

void TankBulletMovement::perform() {
    Collider* pCollider = (Collider*)this->pOwner->findComponentByName(this->pOwner->getName() + " Collider");
    PoolableObject* pPoolableOwner = (PoolableObject*)this->pOwner;
    int nRotation = this->pOwner->getSprite()->getRotation();

    if(pCollider == NULL || pPoolableOwner == NULL) {
        std::cout << "[ERROR] : One or more dependencies are missing." << std::endl;
    }
    else {
        this->fTicks += this->tDeltaTime.asSeconds();
        
        if(this->fTicks > this->fFrameInterval) {
            this->fTicks = 0.0f;

            switch (nRotation) {
                case 0:
                    this->pOwner->getSprite()->move(0.0f, -(this->fSpeed * this->tDeltaTime.asSeconds()));
                    break;
                case 90:
                    this->pOwner->getSprite()->move(this->fSpeed * this->tDeltaTime.asSeconds(), 0.0f);
                    break;
                case 180:
                    this->pOwner->getSprite()->move(0.0f, this->fSpeed * this->tDeltaTime.asSeconds());
                    break;
                case 270:
                    this->pOwner->getSprite()->move(-(this->fSpeed * this->tDeltaTime.asSeconds()), 0.0f);
                    break;
            }

            float fHalfWidth = this->pOwner->getSprite()->getGlobalBounds().width / 2.0f;
            if(this->pOwner->getSprite()->getPosition().x >= (SCREEN_WIDTH + fHalfWidth)) {
                pCollider->setCleanUp(true);
                ObjectPoolManager::getInstance()->getPool(pPoolableOwner->getTag())->releasePoolable(pPoolableOwner);
            }
        }
    }
}
