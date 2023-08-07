#include "ItemDirector.hpp"

using namespace directors;

ItemDirector::ItemDirector(std::string strName) : Component(strName, ComponentType::SCRIPT) {
    this->fSpawnInterval = ITEM_SPAWNRATE;
    this->fTicks = 10.0f;

    this->createItem(PoolTag::ITEM, 5);
}

ItemDirector::~ItemDirector() {}

void ItemDirector::createItem(PoolTag ETag, int nPoolSize) {
    AnimatedTexture* pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(AssetType::ITEM));
    Item* pItem = new Item(ETag, "Item", pTexture);

    GameObjectPool* pGameObjectPool = new GameObjectPool(ETag, nPoolSize, pItem);
    pGameObjectPool->initialize();
    ObjectPoolManager::getInstance()->registerObjectPool(pGameObjectPool);
}

void ItemDirector::spawn() {
    ObjectPoolManager::getInstance()->getPool(PoolTag::ITEM)->requestPoolable();
    std::cout<<"Spawning item"<<std::endl;
}

void ItemDirector::perform() {
    this->fTicks += this->tDeltaTime.asSeconds();

    if(this->fTicks > this->fSpawnInterval) {
        this->fTicks = 0.0f;
        this->spawn();
        this->fSpawnInterval = ITEM_SPAWNRATE + (std::rand() % 6);
    }
}
