#include "Tank.hpp"

using namespace models;

Tank::Tank(PoolTag ETag, std::string strName, AnimatedTexture* pTexture) : PoolableObject(ETag, strName, pTexture) {
    this->bTopBounds = true;
    this->bLeftBounds = true;
    this->bBottomBounds = true;
    this->bRightBounds = true;
}

Tank::~Tank() {}

void Tank::initialize() {
    this->setFrame(0);
    this->centerSpriteOrigin();
    this->pSprite->setPosition(90.0f, 210.0f);

    Renderer* pRendererComponent = new Renderer(this->strName + " Sprite");
    pRendererComponent->assignDrawable(this->pSprite);

    TankInput* pInputComponent = new TankInput(this->strName + " Input");
    TankControls* pControlsComponent = new TankControls(this->strName + " Controls");

    //Collider* pCollider = new Collider(this->strName + " Collider");
    //pCollider->setListener(this);

    this->attachComponent(pRendererComponent);
    this->attachComponent(pInputComponent);
    this->attachComponent(pControlsComponent);
    //this->attachComponent(pCollider);
}

void Tank::onActivate() {
    //float fHalfWidth = this->pShip->getSprite()->getGlobalBounds().width / 2.0f;
    //float fSpacing = 9.0f;

    //this->pSprite->setPosition(this->pShip->getSprite()->getPosition().x + fHalfWidth + fSpacing,
                               //this->pShip->getSprite()->getPosition().y);

    //this->pCollider->cleanCollisions();
    //this->pCollider->setCleanUp(false);
    //PhysicsManager::getInstance()->trackCollider(this->pCollider);

}

void Tank::onRelease() {}

PoolableObject* Tank::clone() {
    //PoolableObject* pClone = new Tank(this->strName, new AnimatedTexture(*this->pTexture), this->pBase);
    PoolableObject* pClone = NULL;
    return pClone;
}

bool Tank::isTopBounds() {
    return this->bTopBounds;
}

bool Tank::isLeftBounds() {
    return this->bLeftBounds;
}

bool Tank::isBottomBounds() {
    return this->bBottomBounds;
}

bool Tank::isRightBounds() {
    return this->bRightBounds;
}
