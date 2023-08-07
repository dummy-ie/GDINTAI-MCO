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

    this->pSprite->setPosition(-100,-100);
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

    std::vector<int> vecPosition = MapManager::getInstance()->getRandomTile(0);

    if(vecPosition[0] != -1){
        this->pSprite->setPosition((vecPosition[0]*32 - 16)+32,(vecPosition[1]*32 - 16)+32);
        MapManager::getInstance()->setMap(vecPosition[0],vecPosition[1],3);
        std::cout<< vecPosition[0] << " " << vecPosition[1] << std::endl;
    }
    else{
        ObjectPoolManager::getInstance()->getPool(PoolTag::ITEM)->releasePoolable(this);
    }
}

void Item::onRelease() {
    if(this->pSprite->getPosition().x > 0){
        std::vector<int> vecPosition = MapManager::getInstance()->getClosestTile(this->pSprite->getPosition().x,this->pSprite->getPosition().y);
        MapManager::getInstance()->setMap(vecPosition[0],vecPosition[1],3);
        this->pSprite->setPosition(-100,-100);
    }
    std::cout << "Item removed" << std::endl;
}

void Item::onCollisionEnter(GameObject* pGameObject) {
    if(pGameObject->getName().find("Tank") != std::string::npos) {
        Collider* pCollider = (Collider*)pGameObject->findComponentByName(pGameObject->getName() + " Collider");
        pCollider->setCollided(this->pCollider, false);
        // this->pCollider->setCleanUp(true);
        PhysicsManager::getInstance()->untrackCollider(this->pCollider);
        PhysicsManager::getInstance()->cleanUp();
        
        Tank* pTank = dynamic_cast<Tank*>(pGameObject);
        Enemy* pEnemy = dynamic_cast<Enemy*>(pGameObject);
        Map* pMap = (Map*)GameObjectManager::getInstance()->findObjectByName("Map");
        std::vector<Base*> vecBases;
        
        if(pTank && pMap){
            switch(this->EType){
                case ItemType::SPEED_UP:
                    std::cout << "speed" << std::endl;
                    pTank->speed(BONUS_SPEED);
                    break;
                case ItemType::SPEED_DOWN:
                    std::cout << "speedn't" << std::endl;
                    pTank->speed(-BONUS_SPEED);
                    break;
                case ItemType::MINES:
                    std::cout << "mines" << std::endl;
                    pTank->damage();
                    break;
                case ItemType::CHAOS:
                    std::cout << "chaos" << std::endl;
                    if(pEnemy){
                        vecBases = pMap->vecEnemyBase;
                        for(Base* pBase : vecBases){
                            pBase->randomizePosition();
                        }
                    }
                    else{
                        vecBases = pMap->vecPlayerBase;
                        for(Base* pBase : vecBases){
                            pBase->randomizePosition();
                        }
                    }
                    break;
                default:
                    break;
            }
            ObjectPoolManager::getInstance()->getPool(PoolTag::ITEM)->releasePoolable(this);
        }   
        
    }
}

void Item::onCollisionContinue(GameObject* pGameObject) {
    pCollider->setCollided(this->pCollider, false);
}

void Item::onCollisionExit(GameObject* pGameObject) {
    pCollider->setCollided(this->pCollider, false);
    PhysicsManager::getInstance()->cleanUp();
}

ItemType Item::getType(){
    return this->EType;
}

PoolableObject* Item::clone() {
    PoolableObject* pClone = new Item(this->ETag, this->strName, new AnimatedTexture(*this->pTexture));
    return pClone;
}