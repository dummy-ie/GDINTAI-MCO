#include "TankBullet.hpp"

using namespace models;

TankBullet::TankBullet(PoolTag ETag, std::string strName, AnimatedTexture* pTexture, Tank* pTank) : PoolableObject(ETag, strName, pTexture) {
    this->pTank = pTank;
    this->pCollider = NULL;
}

void TankBullet::initialize() {
    this->setFrame(0);
    this->centerSpriteOrigin();

    Renderer* pRendererComponent = new Renderer(this->strName + " Sprite");
    pRendererComponent->assignDrawable(this->pSprite);

    this->attachComponent(pRendererComponent);

    this->pCollider = new Collider(this->strName + " Collider");
    this->pCollider->setOffset(sf::FloatRect(15.f, 15.f, -27.f, -27.f));
    this->pCollider->setListener(this);

    this->pMovementComponent = new TankBulletMovement(this->strName + " Bullet Movement");
    this->attachComponent(this->pMovementComponent);

    this->pExplodeComponent = new TankBulletExplode(this->strName + " Bullet Explode");
    this->attachComponent(this->pExplodeComponent);

    this->attachComponent(this->pCollider);
}

void TankBullet::onActivate() {
    float fHalfWidth = this->pTank->getSprite()->getGlobalBounds().width / 2.0f;
    float fSpacing = 3.0f;
    int nRotation = this->pTank->getSprite()->getRotation();
    
    

    this->pSprite->setRotation(nRotation);
    switch (nRotation) {
        case 0:
            this->pSprite->setPosition(this->pTank->getSprite()->getPosition().x,
                                       this->pTank->getSprite()->getPosition().y - fHalfWidth - fSpacing);
            break;
        case 90:
            this->pSprite->setPosition(this->pTank->getSprite()->getPosition().x + fHalfWidth + fSpacing,
                                       this->pTank->getSprite()->getPosition().y);
            break;
        case 180:
            this->pSprite->setPosition(this->pTank->getSprite()->getPosition().x,
                                       this->pTank->getSprite()->getPosition().y + fHalfWidth + fSpacing);
            break;
        case 270:
            this->pSprite->setPosition(this->pTank->getSprite()->getPosition().x - fHalfWidth - fSpacing,
                                       this->pTank->getSprite()->getPosition().y);
            break;
    }
    this->pMovementComponent->start();
    this->pCollider->cleanCollisions();
    this->pCollider->setCleanUp(false);
    PhysicsManager::getInstance()->trackCollider(this->pCollider);
}

void TankBullet::onRelease() {
    //this->pCollider->cleanCollisions();
    //this->pCollider->setCleanUp(false);
    //PhysicsManager::getInstance()->untrackCollider(this->pCollider);
    this->pExplodeComponent->stop();
}

void TankBullet::onCollisionEnter(GameObject* pGameObject) {
    if((pGameObject->getName().find("Tank") != std::string::npos && pGameObject->getName() != this->pTank->getName())||
        pGameObject->getName().find("Border") != std::string::npos || pGameObject->getName().find("Based") != std::string::npos) {
        Collider* pCollider = (Collider*)pGameObject->findComponentByName(pGameObject->getName() + " Collider");
        pCollider->setCollided(this->pCollider, false);
        // this->pCollider->setCleanUp(true);
        this->pExplodeComponent->start();
        this->pMovementComponent->stop();
        PhysicsManager::getInstance()->untrackCollider(this->pCollider);
        PhysicsManager::getInstance()->cleanUp();
        if (pGameObject->getName().find("Enemy Tank") != std::string::npos && !(pGameObject->getName().find("Bullet") != std::string::npos)) {
            ScoreView* pScoreView = (ScoreView*)ViewManager::getInstance()->getView(ViewTag::SCORE_VIEW);
            pScoreView->incrementPlayerKill();
        }
        if (pGameObject->getName().find("Player Tank") != std::string::npos && !(pGameObject->getName().find("Bullet") != std::string::npos)) {
            ScoreView* pScoreView = (ScoreView*)ViewManager::getInstance()->getView(ViewTag::SCORE_VIEW);
            pScoreView->incrementEnemyKill();
        }
        
    }
}

void TankBullet::onCollisionContinue(GameObject* pGameObject) {}

void TankBullet::onCollisionExit(GameObject* pGameObject) {}

PoolableObject* TankBullet::clone() {
    PoolableObject* pClone = new TankBullet(this->ETag, this->strName, new AnimatedTexture(*this->pTexture), this->pTank);
    return pClone;
}