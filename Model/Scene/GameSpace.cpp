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
    this->createTimer();
    this->createScore();
    this->createGameOverInterface();
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

    pComponentHolder = new EmptyGameObject("Tank Director Holder");
    TankDirector* pTankDirector = new TankDirector("Tank Director");
    pComponentHolder->attachComponent(pTankDirector);
    this->registerObject(pComponentHolder);

    pComponentHolder = new EmptyGameObject("Item Director Holder");
    ItemDirector* pItemDirector = new ItemDirector("Item Director");
    pComponentHolder->attachComponent(pItemDirector);
    this->registerObject(pComponentHolder);
}

void GameSpace::createObjectPools() {
    AnimatedTexture* pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(AssetType::BULLET));

    //Tank* pPlayerTank = (Tank*)GameObjectManager::getInstance()->findObjectByName("Player Tank");

    //GameObjectPool* pBulletPool = new GameObjectPool(PoolTag::PLAYER_TANK_BULLET, 1, new TankBullet(PoolTag::PLAYER_TANK_BULLET, "Player Bullet", pTexture, pPlayerTank), NULL);
    //pBulletPool->initialize();
    //ObjectPoolManager::getInstance()->registerObjectPool(pBulletPool);

    //Tank* pEnemyTank = (Tank*)GameObjectManager::getInstance()->findObjectByName("Enemy Tank");

    //pBulletPool = new GameObjectPool(PoolTag::ENEMY_TANK_BULLET, 1, new TankBullet(PoolTag::ENEMY_TANK_BULLET, "Enemy Bullet", pTexture, pEnemyTank), NULL);
    //pBulletPool->initialize();
    //ObjectPoolManager::getInstance()->registerObjectPool(pBulletPool);

    //pBulletPool = new GameObjectPool(PoolTag::TANK_BULLET, 1, new TankBullet("Player Bullet", pTexture, pTank), NULL);
    //pBulletPool->initialize();
    //ObjectPoolManager::getInstance()->registerObjectPool(pBulletPool);
}

void GameSpace::createMap()
{
    Map *pMap = new Map(MapManager::getInstance()->getMap());
    this->registerObject(pMap);


    // AssetType EType = AssetType::STONE;
    // AnimatedTexture* pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));
    // Wall* pWall = new Wall("Stone Wall", pTexture, sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    // this->registerObject(pWall);
}

void GameSpace::createTanks()
{
    //AssetType EType = AssetType::PLAYER_TANK;
    //AnimatedTexture *pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));
    //Player *pPlayer = new Player(PoolTag::PLAYER_TANK, "Player Tank", pTexture);
    //this->registerObject(pPlayer);
    //pPlayer->getSprite()->setPosition(16.f, 16.f);
    //pPlayer->getRectangle()->setPosition(16.f, 16.f);

    //EType = AssetType::ENEMY_TANK;
    //pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));
   // Enemy* pEnemy = new Enemy(PoolTag::ENEMY_TANK, "Enemy Tank", pTexture);
    //this->registerObject(pEnemy);
    //pEnemy->getSprite()->setPosition(208.f, 208.f);
    //pEnemy->getRectangle()->setPosition(208.f, 208.f);
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

void GameSpace::createTimer()
{
    TimerView* pTimerView = new TimerView("Game Space Timer");
    this->registerObject(pTimerView);
}

void GameSpace::createScore()
{
}

void GameSpace::createGameOverInterface()
{
    GameOverScreen* pGameOver = new GameOverScreen("Game Over Screen");
    this->registerObject(pGameOver);
    // pGameOver->setEnabled(true);
}
