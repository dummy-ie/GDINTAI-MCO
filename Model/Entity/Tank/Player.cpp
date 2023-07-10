#include "Player.hpp"

using namespace models;

Player::Player(PoolTag ETag, std::string strName, AnimatedTexture* pTexture) : Tank(ETag, strName, pTexture) {}

Player::~Player() {}

void Player::initialize() {
    this->setFrame(0);
    this->centerSpriteOrigin();

    Renderer* pRendererComponent = new Renderer(this->strName + " Sprite");
    pRendererComponent->assignDrawable(this->pSprite);

    TankInput* pInputComponent = new TankInput(this->strName + " Input");
    TankControls* pControlsComponent = new TankControls(this->strName + " Controls");

    this->CBounds = sf::FloatRect(100.f + 7.f, 100.f - 2.f, this->getSprite()->getGlobalBounds().width - 14.f, 1.f);
    //sf::FloatRect COffset = sf::FloatRect(this->getGlobalBounds().left + 7.f, this->getGlobalBounds().top - 2.f, this->getSprite()->getGlobalBounds().width - 14.f, 1.f);
    Collider* pCollider = new Collider(this->strName + " Collider");
    //pCollider->setOffset(COffset);
    pCollider->setListener(this);
    
    this->pRectangle = new sf::RectangleShape(sf::Vector2f(this->CBounds.width, this->CBounds.height));
    //this->pRectangle->setPosition(COffset.left, COffset.top);
    this->pRectangle->setFillColor(sf::Color(255.f, 0.f, 0.f, 100.f));
    Renderer* pRectangleRenderer = new Renderer(this->strName + " Rectangle");
    pRectangleRenderer->assignDrawable(this->pRectangle);

    
    this->attachComponent(pRendererComponent);
    this->attachComponent(pRectangleRenderer);
    this->attachComponent(pInputComponent);
    this->attachComponent(pControlsComponent);
    this->attachComponent(pCollider);

    PhysicsManager::getInstance()->trackCollider(pCollider);
}

sf::FloatRect Player::getGlobalBounds() {
    return this->CBounds;
}