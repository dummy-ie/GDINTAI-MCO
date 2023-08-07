#include "Player.hpp"

using namespace models;

Player::Player(PoolTag ETag, std::string strName, AnimatedTexture* pTexture) : Tank(ETag, strName, pTexture) {}

Player::~Player() {}

void Player::initialize() {
    this->setFrame(0);
    this->centerSpriteOrigin();
    this->vecSpawn = sf::Vector2f(16.f, 16.f);

    // this->attachComponent(pRendererComponent);

    this->pSpeederComponent = new Speeder(this->strName + " Speeder");
    this->pSpeederComponent->setSpeedable(this);
    this->attachComponent(this->pSpeederComponent);

    TankInput* pInputComponent = new TankInput(this->strName + " Input");
    TankControls* pControlsComponent = new TankControls(this->strName + " Controls");

    // this->CBounds = sf::FloatRect(100.f + 7.f, 100.f - 2.f, this->getSprite()->getGlobalBounds().width - 14.f, 1.f);
    //sf::FloatRect COffset = sf::FloatRect(this->getGlobalBounds().left + 7.f, this->getGlobalBounds().top - 2.f, this->getSprite()->getGlobalBounds().width - 14.f, 1.f);
    this->pCollider = new Collider(this->strName + " Collider");
    COffset = sf::FloatRect(4.f, 0.f, -8.f, -24.f); // top
    // COffset = sf::FloatRect(4.f, 24.f, -8.f, -24.f); // bot
    // COffset = sf::FloatRect(0.f, 4.f, -24.f, -8.f); // left
    // COffset = sf::FloatRect(24.f, 4.f, -24.f, -8.f); // right
    this->pCollider->setOffset(COffset);
    this->pCollider->setListener(this);
    this->attachComponent(this->pCollider);

    pRectangle = new sf::RectangleShape(sf::Vector2f(this->pCollider->getGlobalBounds().width, this->pCollider->getGlobalBounds().height));
    // pRectangle->setOrigin(8.f, 8.f);
    pRectangle->setPosition(100.f + this->pCollider->getGlobalBounds().left, 100.f + this->pCollider->getGlobalBounds().top);
    pRectangle->setFillColor(sf::Color(255.f, 0.f, 0.f, 100.f));
    // pRendererComponent = new Renderer(this->strName + " Rectangle");
    // pRendererComponent->assignDrawable(this->pRectangle);
    Renderer* pRectangleRenderer = new Renderer(this->strName + " Rectangle");
    pRectangleRenderer->assignDrawable(pRectangle);

    Renderer* pRendererComponent = new Renderer(this->strName + " Sprite");
    pRendererComponent->assignDrawable(this->pSprite);
    
    this->pSprite->setPosition(this->vecSpawn);

    this->pKillableComponent = new Killable(this->strName + " Killable");

    this->pDamagerComponent = new Damager(this->strName + " Damager");
    this->pDamagerComponent->setDamageable(this);

    this->attachComponent(pRendererComponent);
    this->attachComponent(pRectangleRenderer);
    this->attachComponent(pRectangleRenderer);
    this->attachComponent(pInputComponent);
    this->attachComponent(pControlsComponent);
    this->attachComponent(this->pKillableComponent);
    this->attachComponent(this->pDamagerComponent);

    AnimatedTexture* pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(AssetType::BULLET));
    GameObjectPool* pBulletPool = new GameObjectPool(PoolTag::PLAYER_TANK_BULLET, 1, new TankBullet(PoolTag::PLAYER_TANK_BULLET, this->strName + " Bullet", pTexture, this), NULL);
    pBulletPool->initialize();
    ObjectPoolManager::getInstance()->registerObjectPool(pBulletPool);
}

void Player::onActivate()
{   
    PhysicsManager::getInstance()->trackCollider(this->pCollider);
    this->pSprite->setPosition(this->vecSpawn);
}

void Player::onRelease() {
    PhysicsManager::getInstance()->untrackCollider(this->pCollider);
}

PoolableObject *Player::clone() {
    Player* pClone = new Player(this->ETag, this->strName, this->pTexture);
    return pClone;
}