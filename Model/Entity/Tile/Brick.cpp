#include "Brick.hpp"

using namespace models;

Brick::Brick(std::string strName, AnimatedTexture* pTexture, sf::Vector2f CPosition) : Tile(strName, pTexture, CPosition) {

}

Brick::~Brick() {}

void Brick::initialize() {
    if(COLLIDER_VISIBILITY)
        this->CColor = sf::Color(255, 0, 0, 100);
    else
        this->CColor = sf::Color::Transparent;
        
    this->centerSpriteOrigin();
    this->setFrame(0);
    this->getSprite()->setPosition(this->CPosition);

    this->pRectangle = new sf::RectangleShape(sf::Vector2f(16.f, 16.f));
    this->pRectangle->setFillColor(this->CColor);
    this->pRectangle->setOrigin(8.f, 8.f);
    this->pRectangle->setPosition(this->getSprite()->getPosition());

    Renderer* pRendererComponent = new Renderer(this->strName + " Sprite");
    pRendererComponent->assignDrawable(this->pSprite);

    this->attachComponent(pRendererComponent);

    pRendererComponent = new Renderer(this->strName + " Rectangle");
    pRendererComponent->assignDrawable(this->pRectangle);

    this->attachComponent(pRendererComponent);

    float fSize = 5.0f;
    float fBleed = 5.0f;

    Border* pBorder = new Border(this->strName + " Border", this->getGlobalBounds());
    this->attachChild(pBorder);

    this->pDamagerComponent = new Damager(this->strName + " Damager");
    this->pDamagerComponent->setDamageable(this);
    this->attachComponent(this->pDamagerComponent);
}

void Brick::damage() {
    std::cout << "damage";
    this->incrementFrame();
    this->pDamagerComponent->stop();
    if (this->getCurrentFrame() >= this->getFrameSize() - 1) {
        this->getParent()->detachChild(this);
        std::vector<int> vecLocation = MapManager::getInstance()->getClosestTile(this->getSprite()->getPosition().x, this->getSprite()->getPosition().y);
        MapManager::getInstance()->setMap(vecLocation[0], vecLocation[1], 0);
    }
}