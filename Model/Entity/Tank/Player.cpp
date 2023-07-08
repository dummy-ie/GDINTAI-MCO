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

    //Collider* pCollider = new Collider(this->strName + " Collider");
    //pCollider->setListener(this);

    this->attachComponent(pRendererComponent);
    this->attachComponent(pInputComponent);
    this->attachComponent(pControlsComponent);
    //this->attachComponent(pCollider);
}