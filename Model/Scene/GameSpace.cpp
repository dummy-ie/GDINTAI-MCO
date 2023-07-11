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

void GameSpace::createMap()
{
    std::vector<std::vector<int>> vecMap = { // -1 is outside the game space, 0 is free
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, // padding layer
        {-1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, -1},
        {-1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, -1},
        {-1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, -1}, // the game still struggles with a lot of colliders
        {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1}, 
        {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
        {-1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, -1},
        {-1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, -1},
        {-1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, -1},
        {-1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, -1},
        {-1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, -1},
        {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1}, // 13x13
        // {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
        // {-1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, -1},
        // {-1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, -1},
        // {-1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, // padding layer
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
    pPlayer->getSprite()->setPosition(100.f, 100.f);

    // EType = AssetType::ENEMY_TANK;
    // pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));
    // Enemy* pEnemy = new Enemy(PoolTag::TANK, "Enemy Tank", pTexture);
    // this->registerObject(pEnemy);
}

void GameSpace::createBorders()
{
    int fSize = 24.0f;

    // 4 borders for the whole screen should be fine and wont contribute much to lag
    // this->registerObject(new Border("Border", 
    //                                 sf::FloatRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT)));
    
    this->registerObject(new Border("Top Border",
                                    sf::FloatRect(0.0f, 0.0f, SCREEN_WIDTH, fSize)));

    this->registerObject(new Border("Left Border",
                                    sf::FloatRect(0.0f, 0.0f, fSize, SCREEN_HEIGHT)));

    this->registerObject(new Border("Bottom Border",
                                    sf::FloatRect(0.0f, SCREEN_HEIGHT - fSize, SCREEN_WIDTH, fSize)));

    this->registerObject(new Border("Right Border",
                                    sf::FloatRect(SCREEN_WIDTH - fSize, 0.0f, fSize, SCREEN_HEIGHT)));
}