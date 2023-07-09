#include "Enemy.hpp"

using namespace models;

Enemy::Enemy(PoolTag ETag, std::string strName, AnimatedTexture* pTexture) : Tank(ETag, strName, pTexture) {}

Enemy::~Enemy() {}

void Enemy::initialize() {
    this->setFrame(0);
    this->centerSpriteOrigin();
    this->pSprite->setScale(2.f, 2.f);

    Renderer* pRendererComponent = new Renderer(this->strName + " Sprite");
    pRendererComponent->assignDrawable(this->pSprite);

    TankControls* pControlsComponent = new TankControls(this->strName + " Controls");

    //Collider* pCollider = new Collider(this->strName + " Collider");
    //pCollider->setListener(this);

    this->attachComponent(pRendererComponent);
    this->attachComponent(pControlsComponent);
    //this->attachComponent(pCollider);
}