#include "Wall.hpp"

using namespace models;

Wall::Wall(std::string strName, AnimatedTexture* pTexture, sf::Vector2f CPosition, sf::Vector2f vecBlockPart) : Tile(strName, pTexture, CPosition), vecBlockPart(vecBlockPart) {

}

Wall::~Wall() {}

void Wall::initialize() {
    this->setFrame(0);
    this->getSprite()->setPosition(this->CPosition);
    this->centerSpriteOrigin();

    Renderer* pRendererComponent = new Renderer(this->strName + " Sprite");
    pRendererComponent->assignDrawable(this->pSprite);

    this->attachComponent(pRendererComponent);

    float fSize = 5.0f;
    float fBleed = 5.0f;

    Border* pTopBorder = new Border(this->strName + " Top Border", sf::FloatRect(this->pSprite->getPosition().x, this->pSprite->getPosition().y + this->getGlobalBounds().height - fSize - fBleed, this->getGlobalBounds().width - 8.0f, fSize));
    Border* pLeftBorder = new Border(this->strName + " Left Border", sf::FloatRect(this->pSprite->getPosition().x + this->getGlobalBounds().width - fSize - fBleed, this->pSprite->getPosition().y, fSize, this->getGlobalBounds().height - 8.0f));
    Border* pBotBorder = new Border(this->strName + " Bottom Border", sf::FloatRect(this->pSprite->getPosition().x, this->pSprite->getPosition().y - fBleed, this->getGlobalBounds().width - 8.0f, fSize));
    Border* pRightBorder = new Border(this->strName + " Right Border", sf::FloatRect(this->pSprite->getPosition().x - fBleed, this->pSprite->getPosition().y, fSize, this->getGlobalBounds().height - 8.0f));

    if (this->vecBlockPart == sf::Vector2f(0, 0))
    {
        this->attachChild(pTopBorder);
        this->attachChild(pLeftBorder);
    }
    else if (this->vecBlockPart == sf::Vector2f(0, 1))
    {
        this->attachChild(pTopBorder);
        this->attachChild(pRightBorder);
    }
    else if (this->vecBlockPart == sf::Vector2f(1, 0))
    {
        this->attachChild(pBotBorder);
        this->attachChild(pLeftBorder);
    }
    else if (this->vecBlockPart == sf::Vector2f(1, 1))
    {
        this->attachChild(pBotBorder);
        this->attachChild(pRightBorder);
    }
    else
    {
        this->attachChild(pTopBorder);
        this->attachChild(pLeftBorder);
        this->attachChild(pBotBorder);
        this->attachChild(pRightBorder);
    }
}