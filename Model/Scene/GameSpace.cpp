#include "GameSpace.hpp"

using namespace scenes;

GameSpace::GameSpace() : Scene(SceneTag::GAME_SPACE) {}

GameSpace::~GameSpace() {}

void GameSpace::onLoadResources()
{
}

void GameSpace::onLoadObjects()
{
    this->createNullObjectComponents();
    this->createMap();
    this->createTanks();
    
    this->createObjectPools();
    this->createBorders();
}

void GameSpace::onUnloadResources()
{
}

void GameSpace::createNullObjectComponents()
{
    std::srand(std::time(NULL));

    EmptyGameObject *pComponentHolder = new EmptyGameObject("Physics Manager Holder");
    PhysicsManager::initialize("Physics Manager System", pComponentHolder);
    this->registerObject(pComponentHolder);
}

void GameSpace::createObjectPools() {
    AnimatedTexture* pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(AssetType::BULLET));

    Tank* pTank = (Tank*)GameObjectManager::getInstance()->findObjectByName("Player Tank");

    GameObjectPool* pBulletPool = new GameObjectPool(PoolTag::TANK_BULLET, 1, new TankBullet("Player Bullet", pTexture, pTank), NULL);
    pBulletPool->initialize();
    ObjectPoolManager::getInstance()->registerObjectPool(pBulletPool);

    //pTank = (Tank*)GameObjectManager::getInstance()->findObjectByName("Enemy Tank");
    //pBulletPool = new GameObjectPool(PoolTag::TANK_BULLET, 1, new TankBullet("Player Bullet", pTexture, pTank), NULL);
    //pBulletPool->initialize();
    //ObjectPoolManager::getInstance()->registerObjectPool(pBulletPool);
}

void GameSpace::createMap()
{
    std::vector<std::vector<int>> vecMap = { // 0 is outside the game space, 0 is free
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // padding layer
        {0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0},
        {0, 2, 0, 2, 0, 2, 1, 2, 0, 2, 0, 2, 0},
        {0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0}, // the game still struggles with a lot of colliders
        {0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 2, 0}, 
        {0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0},
        {1, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 1},
        {0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0},
        {0, 2, 0, 2, 0, 2, 2, 2, 0, 2, 0, 2, 0},
        {0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0},
        {0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 2, 0},
        {0, 2, 0, 2, 0, 2, 2, 2, 0, 2, 0, 2, 0},
        {0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0} // 13x13
    };

    Map *pMap = new Map(vecMap);
    this->registerObject(pMap);

    // AssetType EType = AssetType::STONE;
    // AnimatedTexture* pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));
    // Wall* pWall = new Wall("Stone Wall", pTexture, sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    // this->registerObject(pWall);
}

void GameSpace::createTanks()
{
    AssetType EType = AssetType::PLAYER_TANK;
    AnimatedTexture *pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));
    Player *pPlayer = new Player(PoolTag::TANK, "Player Tank", pTexture);
    this->registerObject(pPlayer);
    pPlayer->getSprite()->setPosition(16.f, 16.f);
    pPlayer->getRectangle()->setPosition(16.f, 16.f);

    // EType = AssetType::ENEMY_TANK;
    // pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));
    // Enemy* pEnemy = new Enemy(PoolTag::TANK, "Enemy Tank", pTexture);
    // this->registerObject(pEnemy);
}

void GameSpace::createBorders()
{
    int fSize = 32.0f;

    // 4 borders for the whole screen should be fine and wont contribute much to lag
    // this->registerObject(new Border("Border", 
    //                                 sf::FloatRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT)));
    
    this->registerObject(new Border("Top Border",
                                    sf::FloatRect(0.0f, -fSize, SCREEN_WIDTH, fSize)));

    this->registerObject(new Border("Left Border",
                                    sf::FloatRect(-fSize, 0.0f, fSize, SCREEN_HEIGHT)));

    this->registerObject(new Border("Bottom Border",
                                    sf::FloatRect(0.0f, SCREEN_HEIGHT, SCREEN_WIDTH, fSize)));

    this->registerObject(new Border("Right Border",
                                    sf::FloatRect(SCREEN_WIDTH, 0.0f, fSize, SCREEN_HEIGHT)));
}