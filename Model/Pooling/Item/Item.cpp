#include "Item.hpp"

using namespace models;

Item::Item(PoolTag ETag, std::string strName, AnimatedTexture* pTexture) : PoolableObject(ETag, strName, pTexture) {
    this->pCollider = NULL;
}

void Item::initialize() {
    this->setFrame(0);
    this->centerSpriteOrigin();

    Renderer* pRendererComponent = new Renderer(this->strName + " Sprite");
    pRendererComponent->assignDrawable(this->pSprite);

    this->attachComponent(pRendererComponent);

    this->pCollider = new Collider(this->strName + " Collider");
    this->pCollider->setOffset(sf::FloatRect(15.f, 15.f, -27.f, -27.f));
    this->pCollider->setListener(this);

    this->attachComponent(this->pCollider);
}

void Item::randomizeType(){
    int nType = (std::rand() % 4);
    this->setFrame(nType);
    this->EType = (ItemType)nType;
}

void Item::onActivate() {
    this->pCollider->cleanCollisions();
    this->pCollider->setCleanUp(false);
    PhysicsManager::getInstance()->trackCollider(this->pCollider);
    this->randomizeType();
}

void Item::onRelease() {
    
}

void Item::onCollisionEnter(GameObject* pGameObject) {
    if(pGameObject->getName().find("Tank") != std::string::npos) {
        Collider* pCollider = (Collider*)pGameObject->findComponentByName(pGameObject->getName() + " Collider");
        pCollider->setCollided(this->pCollider, false);
        // this->pCollider->setCleanUp(true);
        PhysicsManager::getInstance()->untrackCollider(this->pCollider);
        PhysicsManager::getInstance()->cleanUp();
        
        switch(this->EType){
            case ItemType::SPEED_UP:
                break;
            case ItemType::SPEED_DOWN:
                break;
            case ItemType::MINES:
                break;
            case ItemType::CHAOS:
                break;
            default:
                    break;
        }
    }
}

void Item::onCollisionContinue(GameObject* pGameObject) {}

void Item::onCollisionExit(GameObject* pGameObject) {}

void Item::getType(){
    return this->EType;
}

PoolableObject* Item::clone() {
    PoolableObject* pClone = new Item(this->ETag, this->strName, new AnimatedTexture(*this->pTexture));
    return pClone;
}