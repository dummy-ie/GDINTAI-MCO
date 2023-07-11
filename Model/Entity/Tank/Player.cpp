#include "Player.hpp"

using namespace models;

Player::Player(PoolTag ETag, std::string strName, AnimatedTexture* pTexture) : Tank(ETag, strName, pTexture) {}

Player::~Player() {}

void Player::initialize() {
    this->setFrame(0);
    this->centerSpriteOrigin();
    this->centerSpriteOrigin();

    // this->attachComponent(pRendererComponent);

    TankInput* pInputComponent = new TankInput(this->strName + " Input");
    TankControls* pControlsComponent = new TankControls(this->strName + " Controls");

    // this->CBounds = sf::FloatRect(100.f + 7.f, 100.f - 2.f, this->getSprite()->getGlobalBounds().width - 14.f, 1.f);
    //sf::FloatRect COffset = sf::FloatRect(this->getGlobalBounds().left + 7.f, this->getGlobalBounds().top - 2.f, this->getSprite()->getGlobalBounds().width - 14.f, 1.f);
    Collider* pCollider = new Collider(this->strName + " Collider");
    COffset = sf::FloatRect(4.f, 0.f, -8.f, -24.f); // top
    // COffset = sf::FloatRect(4.f, 24.f, -8.f, -24.f); // bot
    // COffset = sf::FloatRect(0.f, 4.f, -24.f, -8.f); // left
    // COffset = sf::FloatRect(24.f, 4.f, -24.f, -8.f); // right
    pCollider->setOffset(COffset);
    pCollider->setListener(this);
    this->attachComponent(pCollider);

    pRectangle = new sf::RectangleShape(sf::Vector2f(pCollider->getGlobalBounds().width, pCollider->getGlobalBounds().height));
    // pRectangle->setOrigin(8.f, 8.f);
    pRectangle->setPosition(100.f + pCollider->getGlobalBounds().left, 100.f + pCollider->getGlobalBounds().top);
    pRectangle->setFillColor(sf::Color(255.f, 0.f, 0.f, 100.f));
    // pRendererComponent = new Renderer(this->strName + " Rectangle");
    // pRendererComponent->assignDrawable(this->pRectangle);
    Renderer* pRectangleRenderer = new Renderer(this->strName + " Rectangle");
    pRectangleRenderer->assignDrawable(pRectangle);

    Renderer* pRendererComponent = new Renderer(this->strName + " Sprite");
    pRendererComponent->assignDrawable(this->pSprite);
    
    this->attachComponent(pRendererComponent);
    this->attachComponent(pRectangleRenderer);
    this->attachComponent(pRectangleRenderer);
    this->attachComponent(pInputComponent);
    this->attachComponent(pControlsComponent);

    PhysicsManager::getInstance()->trackCollider(pCollider);
}

sf::FloatRect Player::getGlobalBounds() {
    return this->getSprite()->getGlobalBounds();
}