#include "TankControls.hpp"

using namespace components;

TankControls::TankControls(std::string strName) : Component(strName, ComponentType::SCRIPT) {
    this->fSpeed = 300.0f;
}

void TankControls::perform() {
    Tank* pOwner = (Tank*)this->pOwner;
    TankInput* pInput = (TankInput*)this->getOwner()->findComponentByName(this->pOwner->getName() + " Input");
    
    if(pInput == NULL) {
        std::cout << "[ERROR] : One or more dependencies are missing." << std::endl;
    }
    else {
        float fOffset = this->fSpeed * this->tDeltaTime.asSeconds();
        
        if(pInput->isUp()) {
            this->getOwner()->getSprite()->setRotation(0.0f);
            if (pOwner->isTopBounds())
                this->getOwner()->getSprite()->move(0.0f, -fOffset);
        }

        if(pInput->isDown()) {
            this->getOwner()->getSprite()->setRotation(180.0f);
            if (pOwner->isBottomBounds())
                this->getOwner()->getSprite()->move(0.0f, fOffset);
        }
        
        if(pInput->isLeft()) {
            this->getOwner()->getSprite()->setRotation(270.0f);
            if (pOwner->isLeftBounds())
                this->getOwner()->getSprite()->move(-fOffset, 0.0f);
        }

        if(pInput->isRight()) {
            this->getOwner()->getSprite()->setRotation(90.0f);
            if (pOwner->isRightBounds())
                this->getOwner()->getSprite()->move(fOffset, 0.0f);
        }

        if(pInput->isSpace()) {
            this->getOwner()->getSprite()->setPosition(64, 64);
            pInput->resetSpace();
            //ObjectPoolManager::getInstance()->getPool(PoolTag::PLAYER_BULLET)->requestPoolable();
        }
    }
}
