#include "TankBullet.hpp"

using namespace models;

TankBullet::TankBullet(std::string strName, AnimatedTexture* pTexture, Tank* pTank) : PoolableObject(PoolTag::TANK_BULLET, strName, pTexture) {
    this->pTank = pTank;
    this->pCollider = NULL;
}

void TankBullet::initialize() {
    std::cout << "hi";
    this->setFrame(0);
    this->centerSpriteOrigin();

    Renderer* pRendererComponent = new Renderer(this->strName + " Sprite");
    pRendererComponent->assignDrawable(this->pSprite);

    this->attachComponent(pRendererComponent);

    this->pCollider = new Collider(this->strName + " Collider");
    this->pCollider->setListener(this);

    this->attachComponent(this->pCollider);
}

void TankBullet::onActivate() {
    float fHalfWidth = this->pTank->getSprite()->getGlobalBounds().width / 2.0f;
    float fSpacing = 9.0f;

    this->pSprite->setPosition(this->pTank->getSprite()->getPosition().x + fHalfWidth + fSpacing,
                               this->pTank->getSprite()->getPosition().y);
    this->pCollider->cleanCollisions();
    this->pCollider->setCleanUp(false);
    PhysicsManager::getInstance()->trackCollider(this->pCollider);
}

void TankBullet::onRelease() {}

void TankBullet::onCollisionEnter(GameObject* pGameObject) {}

void TankBullet::onCollisionContinue(GameObject* pGameObject) {}

void TankBullet::onCollisionExit(GameObject* pGameObject) {}

PoolableObject* TankBullet::clone() {
    PoolableObject* pClone = new TankBullet(this->strName, new AnimatedTexture(*this->pTexture), this->pTank);
    return pClone;
}