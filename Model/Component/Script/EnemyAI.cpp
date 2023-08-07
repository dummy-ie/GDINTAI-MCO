#include "EnemyAI.hpp"

using namespace ai;
using namespace components;

EnemyAI::EnemyAI(std::string strName) : Component(strName, ComponentType::SCRIPT) {
    this->fSpeed = 80.f;
    this->fFrameInterval = 20.f;
    this->fTicks = 0.0f;

    this->nPrevMove = -1;

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

        if(this->nX == -1 || this->nY == -1){
            vecPosition = MapManager::getInstance()->getClosestTile(pOwner->getSprite()->getPosition().x,pOwner->getSprite()->getPosition().y);
            this->nX = vecPosition[0];
            this->nY = vecPosition[1];
        }

        if(MapManager::getInstance()->isCentered(pOwner->getSprite()->getPosition().x,pOwner->getSprite()->getPosition().y,this->nX,this->nY,1.5)){
            //std::cout << "AI location update " << this->nX << " " << this->nY << std::endl;
            vecPosition = MapManager::getInstance()->getClosestTile(pOwner->getSprite()->getPosition().x,pOwner->getSprite()->getPosition().y);
            this->nX = vecPosition[0];
            this->nY = vecPosition[1];
        }

        //std::cout << "AI location " << this->nX << " " << this->nY << std::endl;
        
        Player* pPlayer;
        pPlayer = dynamic_cast<Player*>(GameObjectManager::getInstance()->findObjectByName("Player Tank"));

        if(pPlayer){
            vecPlayerPosition = MapManager::getInstance()->getClosestTile(pPlayer->getSprite()->getPosition().x,pPlayer->getSprite()->getPosition().y);

            Point pointStart = {vecPlayerPosition[0],vecPlayerPosition[1]};
            Point pointEnd = {this->nX, this->nY};
            
            std::vector<std::vector<int>> vecMap = MapManager::getInstance()->getMap();
            std::vector<Point> vecPath = findPath(vecMap, pointStart, pointEnd);

            float fOffset = (this->fSpeed + pOwner->getBonusSpeed()) * this->tDeltaTime.asSeconds();

            if(!vecPath.empty() && vecPath.size() > 2){

                //right
                if(vecPath[1].x > this->nX){
                    this->getOwner()->getSprite()->setRotation(90.0f);
                    pCollider->setOffset(sf::FloatRect(24.f, 4.f, -24.f, -8.f));
                    // ((Player*)(this->getOwner()))->pRectangle->setRotation(90.0f);
                    if (pOwner->isRightBounds())
                    {
                        this->getOwner()->getSprite()->move(fOffset, 0.0f);
                        // pOwner->moveBounds(fOffset, 0.0f);
                        pOwner->getRectangle()->move(fOffset, 0.0f);
                    }
                    this->nPrevMove = 0;
                }
                //left
                else if(vecPath[1].x < this->nX){
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
                    this->nPrevMove = 1;
                }
                //up
                else if(vecPath[1].y < this->nY){
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
                    this->nPrevMove = 2;
                }
                //down
                else if(vecPath[1].y > this->nY){
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
                    this->nPrevMove = 3;
                }
                /*
                else{
                    this->fTicks += this->tDeltaTime.asSeconds();
                    if (this->fTicks > this->fFrameInterval) {
                        this->fTicks = 0.0f;
                        this->getOwner()->incrementFrame();
                    }
                }
                */

                pOwner->getRectangle()->setSize(sf::Vector2f(pCollider->getGlobalBounds().width, pCollider->getGlobalBounds().height));
                pOwner->getRectangle()->setPosition(pCollider->getGlobalBounds().left,pCollider->getGlobalBounds().top);

                bool bXSame = true;
                bool bYSame = true;

                int nPrevX = vecPath[0].x;
                int nPrevY = vecPath[0].y;

                int i = 0;

                for(Point pointPath : vecPath){
                    if(nPrevX != pointPath.x){
                        bXSame = false;
                    }
                    if(nPrevY != pointPath.y){
                        bYSame = false;
                    }
                    //std::cout << "Path " << i << ": " << pointPath.x << " " << pointPath.y << std::endl;
                    i++;
                    nPrevX = pointPath.x;
                    nPrevY = pointPath.y;
                }
                
                if((bXSame && !bYSame)|| (bYSame && !bXSame)) {
                    //this->getOwner()->getSprite()->setPosition(100, 100);
                    // not working
                    ObjectPoolManager::getInstance()->getPool(PoolTag::ENEMY_TANK_BULLET)->requestPoolable();
                    //std::cout << "AI wants to shoot" << std::endl;
                }
                
                //std::cout << "AI going to " << pointStart.x << " " << pointStart.y << std::endl;
                //std::cout << "Next tile value is " << vecMap[vecPath[1].y][vecPath[1].x] << std::endl;
                //std::cout << "AI headed to " << vecPath[1].x << " " << vecPath[1].y << std::endl << std::endl;
                //std::cout << std::endl;

            }
            else if(!vecPath.empty()){
                //right
                if(vecPath[1].x > this->nX){
                    this->getOwner()->getSprite()->setRotation(90.0f);
                    pCollider->setOffset(sf::FloatRect(24.f, 4.f, -24.f, -8.f));
                    // ((Player*)(this->getOwner()))->pRectangle->setRotation(90.0f);
                }
                //left
                else if(vecPath[1].x < this->nX){
                    this->getOwner()->getSprite()->setRotation(270.0f);
                    pCollider->setOffset(sf::FloatRect(0.f, 4.f, -24.f, -8.f));
                    // ((Player*)(this->getOwner()))->pRectangle->setRotation(270.0f);
                }
                //up
                else if(vecPath[1].y < this->nY){
                    this->getOwner()->getSprite()->setRotation(0.0f);
                    pCollider->setOffset(sf::FloatRect(4.f, 0.f, -8.f, -24.f));
                }
                //down
                else if(vecPath[1].y > this->nY){
                    this->getOwner()->getSprite()->setRotation(180.0f);
                    pCollider->setOffset(sf::FloatRect(4.f, 24.f, -8.f, -24.f));
                }

                pOwner->getRectangle()->setSize(sf::Vector2f(pCollider->getGlobalBounds().width, pCollider->getGlobalBounds().height));
                pOwner->getRectangle()->setPosition(pCollider->getGlobalBounds().left,pCollider->getGlobalBounds().top);

                bool bXSame = true;
                bool bYSame = true;

                int nPrevX = vecPath[0].x;
                int nPrevY = vecPath[0].y;

                int i = 0;

                for(Point pointPath : vecPath){
                    if(nPrevX != pointPath.x){
                        bXSame = false;
                    }
                    if(nPrevY != pointPath.y){
                        bYSame = false;
                    }
                    //std::cout << "Path " << i << ": " << pointPath.x << " " << pointPath.y << std::endl;
                    i++;
                    nPrevX = pointPath.x;
                    nPrevY = pointPath.y;
                }
                
                if((bXSame && !bYSame)|| (bYSame && !bXSame)) {
                    //this->getOwner()->getSprite()->setPosition(100, 100);
                    // not working
                    //ObjectPoolManager::getInstance()->getPool(PoolTag::TANK_BULLET)->requestPoolable();
                    //std::cout << "AI wants to shoot" << std::endl;
                }
            }
            else{
                //std::cout << "AI location " << this->nX << " " << this->nY << std::endl;
                //std::cout << "AI going to " << pointStart.x << " " << pointStart.y << std::endl;
                std::cout << "[AI] : No path." << std::endl << std::endl;
                switch(this->nPrevMove){
                    case 0:
                        this->getOwner()->getSprite()->setRotation(90.0f);
                        pCollider->setOffset(sf::FloatRect(24.f, 4.f, -24.f, -8.f));
                        // ((Player*)(this->getOwner()))->pRectangle->setRotation(90.0f);
                        if (pOwner->isRightBounds())
                        {
                            this->getOwner()->getSprite()->move(fOffset, 0.0f);
                            // pOwner->moveBounds(fOffset, 0.0f);
                            pOwner->getRectangle()->move(fOffset, 0.0f);
                            //this->nPrevMove = 1;
                        }
                        break;
                    case 1:
                        this->getOwner()->getSprite()->setRotation(270.0f);
                        pCollider->setOffset(sf::FloatRect(0.f, 4.f, -24.f, -8.f));
                        // ((Player*)(this->getOwner()))->pRectangle->setRotation(270.0f);
                        if (pOwner->isLeftBounds())
                        {
                            this->getOwner()->getSprite()->move(-fOffset, 0.0f);
                            // pOwner->moveBounds(-fOffset, 0.0f);
                            pOwner->getRectangle()->move(-fOffset, 0.0f);
                            //this->nPrevMove = 0;
                        }
                        break;
                    case 2:
                        this->getOwner()->getSprite()->setRotation(0.0f);
                        pCollider->setOffset(sf::FloatRect(4.f, 0.f, -8.f, -24.f));
                        if (pOwner->isTopBounds())
                        {
                            this->getOwner()->getSprite()->move(0.0f, -fOffset);
                            // pOwner->moveBounds(0.0f, -fOffset);
                            pOwner->getRectangle()->move(0.0f, -fOffset);
                            //this->nPrevMove = 3;
                        }   
                        break;
                    case 3:
                        this->getOwner()->getSprite()->setRotation(180.0f);
                        pCollider->setOffset(sf::FloatRect(4.f, 24.f, -8.f, -24.f));
                        // ((Player*)(this->getOwner()))->pRectangle->setRotation(180.0f);
                        if (pOwner->isBottomBounds())
                        {
                            this->getOwner()->getSprite()->move(0.0f, fOffset);
                            // pOwner->moveBounds(0.0f, fOffset);
                            pOwner->getRectangle()->move(0.0f, fOffset);
                            //this->nPrevMove = 2;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        else{
            std::cout << "[AI] : Unable to locate player." << std::endl;
        }

        
    }
}
