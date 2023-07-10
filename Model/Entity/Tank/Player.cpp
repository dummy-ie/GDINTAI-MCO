#include "Player.hpp"

using namespace models;

Player::Player(PoolTag ETag, std::string strName, AnimatedTexture* pTexture) : Tank(ETag, strName, pTexture) {}

Player::~Player() {}

void Player::initialize() {
    this->setFrame(0);

    Renderer* pRendererComponent = new Renderer(this->strName + " Sprite");
    pRendererComponent->assignDrawable(this->pSprite);

    TankInput* pInputComponent = new TankInput(this->strName + " Input");
    TankControls* pControlsComponent = new TankControls(this->strName + " Controls");

    Collider* pCollider = new Collider(this->strName + " Collider");
    sf::FloatRect COffset = sf::FloatRect(this->getSprite()->getPosition().x + 7.f, this->getSprite()->getPosition().y - 2.f, this->getSprite()->getGlobalBounds().width - 14.f, 1.f);
    pCollider->setOffset(COffset);
    pCollider->setListener(this);
    
    sf::RectangleShape* pRectangle = new sf::RectangleShape(sf::Vector2f(COffset.width, COffset.height));
    pRectangle->setPosition(COffset.left, COffset.top);
    pRectangle->setFillColor(sf::Color(255.f, 0.f, 0.f, 100.f));
    // Renderer* pRectangleRenderer = new Renderer(this->strName + " Rectangle");
    // pRendererComponent->assignDrawable(pRectangle);

    this->centerSpriteOrigin();
    
    // this->attachComponent(pRectangleRenderer);
    this->attachComponent(pRendererComponent);
    this->attachComponent(pInputComponent);
    this->attachComponent(pControlsComponent);
    this->attachComponent(pCollider);

    PhysicsManager::getInstance()->trackCollider(pCollider);
}