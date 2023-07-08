#include "GameSpace.hpp"

using namespace scenes;

GameSpace::GameSpace() : Scene(SceneTag::GAME_SPACE) {}

GameSpace::~GameSpace() {}

void GameSpace::onLoadResources() {
    
}

void GameSpace::onLoadObjects() {
    this->createMap();
    this->createTanks();
}

void GameSpace::onUnloadResources() {
    
}

void GameSpace::createMap() {

}

void GameSpace::createTanks() {
    AssetType EType = AssetType::PLAYER_TANK;
    AnimatedTexture* pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));
    Player* pPlayer = new Player(PoolTag::TANK, "Player Tank", pTexture);
    this->registerObject(pPlayer);

    EType = AssetType::ENEMY_TANK;
    pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));
    Enemy* pEnemy = new Enemy(PoolTag::TANK, "Enemy Tank", pTexture);
    this->registerObject(pEnemy);
}