#include "TankDirector.hpp"

using namespace directors;

TankDirector::TankDirector(std::string strName) : Component(strName, ComponentType::SCRIPT) {
    this->fSpawnInterval = 10.0f;
    this->fTicks = 10.0f;

    this->createPlayer(PoolTag::PLAYER_TANK, 1);
    this->createEnemy(PoolTag::ENEMY_TANK, 1);
}

TankDirector::~TankDirector() {}

void TankDirector::createPlayer(PoolTag ETag, int nPoolSize) {
    AnimatedTexture* pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(AssetType::PLAYER_TANK));
    Player* pPlayer = new Player(ETag, "Player Tank", pTexture);

    
    
    GameObjectPool* pGameObjectPool = new GameObjectPool(ETag, nPoolSize, pPlayer);
    pGameObjectPool->initialize();
    ObjectPoolManager::getInstance()->registerObjectPool(pGameObjectPool);
}

void TankDirector::createEnemy(PoolTag ETag, int nPoolSize) {
    AnimatedTexture* pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(AssetType::ENEMY_TANK));
    Enemy* pEnemy = new Enemy(ETag, "Enemy Tank", pTexture);

    GameObjectPool* pGameObjectPool = new GameObjectPool(ETag, nPoolSize, pEnemy);
    pGameObjectPool->initialize();
    ObjectPoolManager::getInstance()->registerObjectPool(pGameObjectPool);
}

void TankDirector::spawn() {
    ObjectPoolManager::getInstance()->getPool(PoolTag::PLAYER_TANK)->requestPoolable();
    ObjectPoolManager::getInstance()->getPool(PoolTag::ENEMY_TANK)->requestPoolable();
}

void TankDirector::perform() {
    this->fTicks += this->tDeltaTime.asSeconds();

    if(this->fTicks > this->fSpawnInterval) {
        this->fTicks = 0.0f;
        this->spawn();
    }
}
