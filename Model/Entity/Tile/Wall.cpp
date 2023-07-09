#include "Wall.hpp"

using namespace models;

Wall::Wall(std::string strName, AnimatedTexture* pTexture, sf::Vector2f CPosition) : Tile(strName, pTexture, CPosition) {

}

Wall::~Wall() {}

void Wall::initialize() {
    this->setFrame(0);
    this->centerSpriteOrigin();
    this->getSprite()->setPosition(this->CPosition);

    Renderer* pRendererComponent = new Renderer(this->strName + " Sprite");
    pRendererComponent->assignDrawable(this->pSprite);

    this->attachComponent(pRendererComponent);

    float fSize = 8.0f;

    Border* pBorder = new Border(this->strName + " Top Border", sf::FloatRect(this->pSprite->getPosition().x, this->pSprite->getPosition().y, this->pSprite->getGlobalBounds().width, fSize));
    this->attachChild(pBorder);

    pBorder = new Border(this->strName + " Left Border", sf::FloatRect(this->pSprite->getPosition().x, this->pSprite->getPosition().y, fSize, this->getGlobalBounds().height));
    this->attachChild(pBorder);

    pBorder = new Border(this->strName + " Bottom Border", sf::FloatRect(this->pSprite->getPosition().x, this->getGlobalBounds().height - fSize, this->getGlobalBounds().width, fSize));
    this->attachChild(pBorder);

    pBorder = new Border(this->strName + " Right Border", sf::FloatRect(this->getGlobalBounds().width - fSize, this->pSprite->getPosition().y, fSize, this->getGlobalBounds().height));
    this->attachChild(pBorder);
}