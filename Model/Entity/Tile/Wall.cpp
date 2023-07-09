#include "Wall.hpp"

using namespace models;

Wall::Wall(std::string strName, AnimatedTexture* pTexture) : Tile(strName, pTexture) {

}

Wall::~Wall() {}

void Wall::initialize() {
    this->setFrame(0);
    this->centerSpriteOrigin();

    this->CBounds = this->pSprite->getGlobalBounds();

    Renderer* pRendererComponent = new Renderer(this->strName + " Sprite");
    pRendererComponent->assignDrawable(this->pSprite);

    this->attachComponent(pRendererComponent);
}