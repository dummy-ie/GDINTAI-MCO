#include "TankControls.hpp"

using namespace components;

TankControls::TankControls(std::string strName) : Component(strName, ComponentType::SCRIPT) {
    this->fSpeed = 80.f;
    this->fFrameInterval = 20.f;
    this->fTicks = 0.0f;
}

void TankControls::perform() {
    Tank* pOwner = (Tank*)this->pOwner;
    TankInput* pInput = (TankInput*)this->getOwner()->findComponentByName(this->pOwner->getName() + " Input");
    Collider* pCollider = (Collider*)this->getOwner()->findComponentByName(this->pOwner->getName() + " Collider");
    
    if(pInput == NULL) {
        std::cout << "[ERROR] : One or more dependencies are missing." << std::endl;
    }
    else {
        float fOffset = this->fSpeed * this->tDeltaTime.asSeconds();
        this->fTicks++;
        if (this->fTicks > this->fFrameInterval) {
            this->fTicks = 0.0f;
            this->getOwner()->incrementFrame();
        }

        if(pInput->isUp()) {
            this->getOwner()->getSprite()->setRotation(0.0f);
            pCollider->setOffset(sf::FloatRect(4.f, 0.f, -8.f, -24.f));
            if (pOwner->isTopBounds())
            {
                this->getOwner()->getSprite()->move(0.0f, -fOffset);
                // pOwner->moveBounds(0.0f, -fOffset);
                pOwner->getRectangle()->move(0.0f, -fOffset);
            }   
                // ((Player*)(this->getOwner()))->pRectangle->move(0.0f, -fOffset);
            // }
        }

        if(pInput->isDown()) {
            this->getOwner()->getSprite()->setRotation(180.0f);
            pCollider->setOffset(sf::FloatRect(4.f, 24.f, -8.f, -24.f));
            // ((Player*)(this->getOwner()))->pRectangle->setRotation(180.0f);
            if (pOwner->isBottomBounds())
            {
                this->getOwner()->getSprite()->move(0.0f, fOffset);
                // pOwner->moveBounds(0.0f, fOffset);
                pOwner->getRectangle()->move(0.0f, fOffset);
            }
                // ((Player*)(this->getOwner()))->pRectangle->move(0.0f, fOffset);

            // }
        }
        
        if(pInput->isLeft()) {
            this->getOwner()->getSprite()->setRotation(270.0f);
            pCollider->setOffset(sf::FloatRect(0.f, 4.f, -24.f, -8.f));
            // ((Player*)(this->getOwner()))->pRectangle->setRotation(270.0f);
            if (pOwner->isLeftBounds())
            {
                this->getOwner()->getSprite()->move(-fOffset, 0.0f);
                // pOwner->moveBounds(-fOffset, 0.0f);
                pOwner->getRectangle()->move(-fOffset, 0.0f);
            }
                // ((Player*)(this->getOwner()))->pRectangle->move(-fOffset, 0.0f);
            // }
        }

        if(pInput->isRight()) {
            this->getOwner()->getSprite()->setRotation(90.0f);
            pCollider->setOffset(sf::FloatRect(24.f, 4.f, -24.f, -8.f));
            // ((Player*)(this->getOwner()))->pRectangle->setRotation(90.0f);
            if (pOwner->isRightBounds())
            {
                this->getOwner()->getSprite()->move(fOffset, 0.0f);
                // pOwner->moveBounds(fOffset, 0.0f);
                pOwner->getRectangle()->move(fOffset, 0.0f);
            }
        }

        pOwner->getRectangle()->setSize(sf::Vector2f(pCollider->getGlobalBounds().width, pCollider->getGlobalBounds().height));
        pOwner->getRectangle()->setPosition(pCollider->getGlobalBounds().left,pCollider->getGlobalBounds().top);
        // ((Player*)(this->getOwner()))->pRectangle->setSize(sf::Vector2f(pCollider->getGlobalBounds().width, pCollider->getGlobalBounds().height));
        // ((Player*)(this->getOwner()))->pRectangle->setPosition(pCollider->getGlobalBounds().left,pCollider->getGlobalBounds().top);
        // this->getSprite()->getPosition().x + 8.f, this->getSprite()->getPosition().y - 3.f
        // ((Player*)(this->getOwner()))->pRectangle->setPosition(this->getOwner()->getSprite()->getPosition().x + 8.f, this->getOwner()->getSprite()->getPosition().y - 3.f);

        if(pInput->isSpace()) {
            this->getOwner()->getSprite()->setPosition(100, 100);
            pInput->resetSpace();
            //ObjectPoolManager::getInstance()->getPool(PoolTag::PLAYER_BULLET)->requestPoolable();
        }
    }
}
