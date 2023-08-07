#include "Base.hpp"

using namespace models;

Base::Base(std::string strName, AnimatedTexture* pTexture, sf::Vector2f CPosition, TeamTag ETeam) : Tile(strName, pTexture, CPosition) {
    this->ETeam = ETeam;
}

Base::~Base() {}

void Base::initialize() {
    if(COLLIDER_VISIBILITY)
        this->CColor = sf::Color(255, 0, 0, 100);
    else
        this->CColor = sf::Color::Transparent;
        
    this->centerSpriteOrigin();
    this->setFrame((int)this->ETeam);
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

    Border* pBorder = new Border(this->strName + " Based", this->getGlobalBounds());
    this->attachChild(pBorder);

    this->pDamagerComponent = new Damager(this->strName + " Damager");
    this->pDamagerComponent->setDamageable(this);
    this->attachComponent(this->pDamagerComponent);
}

void Base::damage() {
    this->incrementFrame();
    if(this->ETeam == TeamTag::ENEMY){
        this->incrementFrame();
    }
    this->pDamagerComponent->stop();
    if (this->getCurrentFrame() >= this->getFrameSize() - 1) {
        this->getParent()->detachChild(this);
        std::vector<int> vecLocation = MapManager::getInstance()->getClosestTile(this->getSprite()->getPosition().x, this->getSprite()->getPosition().y);
        //MapManager::getInstance()->setMap(vecLocation[0], vecLocation[1], 0);
    }
    Map* pMap = (Map*)GameObjectManager::getInstance()->findObjectByName("Map");
    pMap->removeBase(this);
}

void Base::randomizePosition(){
    std::vector<int> vecPosition = MapManager::getInstance()->getRandomTile(0);

    if(vecPosition[0] != -1){
        MapManager::getInstance()->setMap(vecPosition[0],vecPosition[1],0);
        this->pSprite->setPosition((vecPosition[0]*32 - 16)+32,(vecPosition[1]*32 - 16)+32);
        this->pRectangle->setPosition((vecPosition[0]*32 - 16)+32,(vecPosition[1]*32 - 16)+32);
        //MapManager::getInstance()->setMap(vecPosition[0],vecPosition[1],4);
    }
    else{
        
    }
}

TeamTag Base::getTeam(){
    return this->ETeam;
}