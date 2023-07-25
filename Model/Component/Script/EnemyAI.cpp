#include "EnemyAI.hpp"

using namespace ai;
using namespace components;

EnemyAI::EnemyAI(std::string strName) : Component(strName, ComponentType::SCRIPT) {
    this->fSpeed = 80.f;
    this->fFrameInterval = 20.f;
    this->fTicks = 0.0f;

    this->nX = -1;
    this->nY = -1;
}

void EnemyAI::perform() {
    Tank* pOwner = (Tank*)this->pOwner;
    //TankInput* pInput = (TankInput*)this->getOwner()->findComponentByName(this->pOwner->getName() + " Input");
    Collider* pCollider = (Collider*)this->getOwner()->findComponentByName(this->pOwner->getName() + " Collider");

    std::vector<int> vecPosition;
    std::vector<int> vecPlayerPosition;
    
    if(pOwner == NULL) {
        std::cout << "[ERROR] : One or more dependencies are missing." << std::endl;
    }
    else {

        vecPosition = MapManager::getInstance()->getClosestTile(pOwner->getSprite()->getPosition().x,pOwner->getSprite()->getPosition().y);
        this->nX = vecPosition[0];
        this->nY = vecPosition[1];
        
        Player* pPlayer;
        pPlayer = dynamic_cast<Player*>(GameObjectManager::getInstance()->findObjectByName("Player Tank"));

        if(pPlayer){
            vecPlayerPosition = MapManager::getInstance()->getClosestTile(pPlayer->getSprite()->getPosition().x,pPlayer->getSprite()->getPosition().y);

            Point pointStart = {vecPlayerPosition[0],vecPlayerPosition[1]};
            Point pointEnd = {this->nX, this->nY};
            
            std::vector<std::vector<int>> vecMap = MapManager::getInstance()->getMap();
            std::vector<Point> vecPath = findPath(vecMap, pointStart, pointEnd);

            float fOffset = this->fSpeed * this->tDeltaTime.asSeconds();

            //right
            if(vecPath[0].x > this->nX){
                this->getOwner()->getSprite()->setRotation(90.0f);
                pCollider->setOffset(sf::FloatRect(24.f, 4.f, -24.f, -8.f));
                // ((Player*)(this->getOwner()))->pRectangle->setRotation(90.0f);
                if (pOwner->isRightBounds())
                {
                    this->getOwner()->getSprite()->move(fOffset, 0.0f);
                    // pOwner->moveBounds(fOffset, 0.0f);
                    pOwner->getRectangle()->move(fOffset, 0.0f);
                }
            }
            //left
            else if(vecPath[0].x < this->nX){
                this->getOwner()->getSprite()->setRotation(270.0f);
                pCollider->setOffset(sf::FloatRect(0.f, 4.f, -24.f, -8.f));
                // ((Player*)(this->getOwner()))->pRectangle->setRotation(270.0f);
                if (pOwner->isLeftBounds())
                {
                    this->getOwner()->getSprite()->move(-fOffset, 0.0f);
                    // pOwner->moveBounds(-fOffset, 0.0f);
                    pOwner->getRectangle()->move(-fOffset, 0.0f);
                }
                    // ((Player*)(this->getOwner()))->pRectangle->move(-fOffset, 0.0f);
                // }
            }
            //up
            else if(vecPath[0].y > this->nY){
                this->getOwner()->getSprite()->setRotation(0.0f);
                pCollider->setOffset(sf::FloatRect(4.f, 0.f, -8.f, -24.f));
                if (pOwner->isTopBounds())
                {
                    this->getOwner()->getSprite()->move(0.0f, -fOffset);
                    // pOwner->moveBounds(0.0f, -fOffset);
                    pOwner->getRectangle()->move(0.0f, -fOffset);
                }   
                    // ((Player*)(this->getOwner()))->pRectangle->move(0.0f, -fOffset);
                // }
            }
            //down
            else if(vecPath[0].y < this->nY){
                this->getOwner()->getSprite()->setRotation(180.0f);
                pCollider->setOffset(sf::FloatRect(4.f, 24.f, -8.f, -24.f));
                // ((Player*)(this->getOwner()))->pRectangle->setRotation(180.0f);
                if (pOwner->isBottomBounds())
                {
                    this->getOwner()->getSprite()->move(0.0f, fOffset);
                    // pOwner->moveBounds(0.0f, fOffset);
                    pOwner->getRectangle()->move(0.0f, fOffset);
                }
                    // ((Player*)(this->getOwner()))->pRectangle->move(0.0f, fOffset);

                // }
            }
            else{
                this->fTicks += this->tDeltaTime.asSeconds();
                if (this->fTicks > this->fFrameInterval) {
                    this->fTicks = 0.0f;
                    this->getOwner()->incrementFrame();
                }
            }

            pOwner->getRectangle()->setSize(sf::Vector2f(pCollider->getGlobalBounds().width, pCollider->getGlobalBounds().height));
            pOwner->getRectangle()->setPosition(pCollider->getGlobalBounds().left,pCollider->getGlobalBounds().top);
            // ((Player*)(this->getOwner()))->pRectangle->setSize(sf::Vector2f(pCollider->getGlobalBounds().width, pCollider->getGlobalBounds().height));
            // ((Player*)(this->getOwner()))->pRectangle->setPosition(pCollider->getGlobalBounds().left,pCollider->getGlobalBounds().top);
            // this->getSprite()->getPosition().x + 8.f, this->getSprite()->getPosition().y - 3.f
            // ((Player*)(this->getOwner()))->pRectangle->setPosition(this->getOwner()->getSprite()->getPosition().x + 8.f, this->getOwner()->getSprite()->getPosition().y - 3.f);

            bool bXSame = true;
            bool bYSame = true;

            int nPrevX = vecPath[0].x;
            int nPrevY = vecPath[0].y;

            for(Point pointPath : vecPath){
                if(nPrevX != pointPath.x){
                    bXSame = false;
                }
                if(nPrevY != pointPath.y){
                    bYSame = false;
                }
                nPrevX = pointPath.x;
                nPrevY = pointPath.y;
            }

            if(bXSame || bYSame) {
                //this->getOwner()->getSprite()->setPosition(100, 100);
                // not working
                ObjectPoolManager::getInstance()->getPool(PoolTag::TANK_BULLET)->requestPoolable();
            }
        }
        else{
            std::cout << "[AI] : Unable to locate player." << std::endl;
        }

        
    }
}
