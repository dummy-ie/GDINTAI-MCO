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

    float fSize = 5.0f;
    float fBleed = 5.0f;

    Border* pBorder = new Border(this->strName + " Top Border", sf::FloatRect(this->pSprite->getPosition().x, this->pSprite->getPosition().y + this->getGlobalBounds().height - fSize - fBleed, this->getGlobalBounds().width - 8.0f, fSize));
    this->attachChild(pBorder);

    pBorder = new Border(this->strName + " Left Border", sf::FloatRect(this->pSprite->getPosition().x + this->getGlobalBounds().width - fSize - fBleed, this->pSprite->getPosition().y, fSize, this->getGlobalBounds().height - 8.0f));
    this->attachChild(pBorder);

    pBorder = new Border(this->strName + " Bottom Border", sf::FloatRect(this->pSprite->getPosition().x, this->pSprite->getPosition().y - fBleed, this->getGlobalBounds().width - 8.0f, fSize));
    this->attachChild(pBorder);

    pBorder = new Border(this->strName + " Right Border", sf::FloatRect(this->pSprite->getPosition().x - fBleed, this->pSprite->getPosition().y, fSize, this->getGlobalBounds().height - 8.0f));
    this->attachChild(pBorder);
}