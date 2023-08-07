#include "EnemyAI.hpp"

using namespace ai;
using namespace components;

EnemyAI::EnemyAI(std::string strName) : Component(strName, ComponentType::SCRIPT) {
    this->fSpeed = AI_SPEED;
    this->fFrameInterval = 0.01f;
    this->fTicks = 0.0f;
    this->fTimeStuck = 0.f;

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
    
    this->fTicks += this->tDeltaTime.asSeconds();

    if(pOwner == NULL) {
        std::cout << "[ERROR] : One or more dependencies are missing." << std::endl;
    }
    else if (this->fTicks > this->fFrameInterval){
        this->fTicks = 0.f;
        vecPosition = MapManager::getInstance()->getClosestTile(pOwner->getSprite()->getPosition().x,pOwner->getSprite()->getPosition().y);
        if(this->nX == -1 || this->nY == -1){
            this->nX = vecPosition[0];
            this->nY = vecPosition[1];
        }

        if(MapManager::getInstance()->isCentered(pOwner->getSprite()->getPosition().x,pOwner->getSprite()->getPosition().y,this->nX,this->nY,1.5)){
            //std::cout << "AI location update " << this->nX << " " << this->nY << std::endl;
            this->nX = vecPosition[0];
            this->nY = vecPosition[1];
        }

        if(this->fTimeStuck > AI_STUCK_TIMER){
            this->fTimeStuck = 0;
            this->getOwner()->getSprite()->setPosition((vecPosition[0]*32-16)+32,(vecPosition[1]*32-16)+32);
            pOwner->getRectangle()->setPosition((vecPosition[0]*32-16)+32,(vecPosition[1]*32-16)+32);
            this->nX = vecPosition[0];
            this->nY = vecPosition[1];
            pOwner->collisionReset();
            std::cout<<"unstucking ai"<<std::endl;
        }

        //std::cout << "AI location " << this->nX << " " << this->nY << std::endl;
        
        Player* pPlayer;
        pPlayer = dynamic_cast<Player*>(GameObjectManager::getInstance()->findObjectByName("Player Tank"));

        if(pPlayer){
            vecPlayerPosition = MapManager::getInstance()->getClosestTile(pPlayer->getSprite()->getPosition().x,pPlayer->getSprite()->getPosition().y);

            Point pointStart = {vecPlayerPosition[0],vecPlayerPosition[1]};
            Point pointEnd = {this->nX, this->nY};
            
            std::vector<Point> vecPoint;
            vecPoint.push_back(pointStart);

            Map* pMap = (Map*)GameObjectManager::getInstance()->findObjectByName("Map");
            for(Base* pBase : pMap->vecPlayerBase){
                std::vector<int> vecBasePosition = MapManager::getInstance()->getClosestTile(pBase->getSprite()->getPosition().x,pBase->getSprite()->getPosition().y);
                Point pointBase = {vecBasePosition[0],vecBasePosition[1]};
                //std::cout<<vecBasePosition[0]<<" "<<vecBasePosition[1]<<std::endl;
                vecPoint.push_back(pointBase);
            }

            std::vector<std::vector<int>> vecMap = MapManager::getInstance()->getMap();
            std::vector<Point> vecPath = findPath(vecMap, pointStart, pointEnd);

            bool bShoot = false;

            if(vecPath.empty()){
                bShoot = true;
                vecPath = findPath(vecMap, pointStart, pointEnd, bShoot);
            }

            int nRand = std::rand() % 5000;
            if(nRand > 4980){
                bShoot = true;
            }
            /*
            nRand = std::rand() % 100;
            if(vecPath.empty() && nRand > 98){
                vecPath = findPath(vecMap, wanderPoint, pointEnd, bShoot);
            }
            */

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
                        this->fTimeStuck += this->tDeltaTime.asSeconds();
                    }
                    else{
                        this->fTimeStuck = 0;
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
                        this->fTimeStuck += this->tDeltaTime.asSeconds();
                    }
                    else{
                        this->fTimeStuck = 0;
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
                        this->fTimeStuck += this->tDeltaTime.asSeconds();
                    }   
                    else{
                        this->fTimeStuck = 0;
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
                        this->fTimeStuck += this->tDeltaTime.asSeconds();
                    }
                    else{
                        this->fTimeStuck = 0;
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
                
                if((bXSame && !bYSame) || (bYSame && !bXSame) || bShoot) {
                    ObjectPoolManager::getInstance()->getPool(PoolTag::ENEMY_TANK_BULLET)->requestPoolable();
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
                    i++;
                    nPrevX = pointPath.x;
                    nPrevY = pointPath.y;
                }
                
                if((bXSame && !bYSame)|| (bYSame && !bXSame)) {
                    ObjectPoolManager::getInstance()->getPool(PoolTag::ENEMY_TANK_BULLET)->requestPoolable();
                }
            }
            else{
                std::cout << "[AI] : No path." << std::endl << std::endl;
                this->fTimeStuck += this->tDeltaTime.asSeconds();
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
                            this->fTimeStuck += this->tDeltaTime.asSeconds();
                            //this->nPrevMove = 1;
                        }
                        else{
                            this->fTimeStuck = 0;
                        }
                        break;
                    case 1:
                        this->getOwner()->getSprite()->setRotation(270.0f);
                        pCollider->setOffset(sf::FloatRect(0.f, 4.f, -24.f, -8.f));
                        if (pOwner->isLeftBounds())
                        {
                            this->getOwner()->getSprite()->move(-fOffset, 0.0f);
                            pOwner->getRectangle()->move(-fOffset, 0.0f);
                            this->fTimeStuck += this->tDeltaTime.asSeconds();
                        }
                        else{
                            this->fTimeStuck = 0;
                        }
                        break;
                    case 2:
                        this->getOwner()->getSprite()->setRotation(0.0f);
                        pCollider->setOffset(sf::FloatRect(4.f, 0.f, -8.f, -24.f));
                        if (pOwner->isTopBounds())
                        {
                            this->getOwner()->getSprite()->move(0.0f, -fOffset);
                            pOwner->getRectangle()->move(0.0f, -fOffset);
                            this->fTimeStuck += this->tDeltaTime.asSeconds();
                        }   
                        else{
                            this->fTimeStuck = 0;
                        }
                        break;
                    case 3:
                        this->getOwner()->getSprite()->setRotation(180.0f);
                        pCollider->setOffset(sf::FloatRect(4.f, 24.f, -8.f, -24.f));
                        if (pOwner->isBottomBounds())
                        {
                            this->getOwner()->getSprite()->move(0.0f, fOffset);
                            pOwner->getRectangle()->move(0.0f, fOffset);
                            this->fTimeStuck += this->tDeltaTime.asSeconds();
                        }
                        else{
                            this->fTimeStuck = 0;
                        }
                        break;
                    default:
                        break;
                }
            }
            pOwner->collisionReset();
        }
        else{
            std::cout << "[AI] : Unable to locate player." << std::endl;
        }

        
    }
}

void EnemyAI::reset(){
    Tank* pOwner = (Tank*)this->pOwner;
    std::vector<int> vecPosition = MapManager::getInstance()->getClosestTile(pOwner->getSprite()->getPosition().x,pOwner->getSprite()->getPosition().y);
    if(pOwner){
        this->nX = vecPosition[0];
        this->nY = vecPosition[1];
    }
}
