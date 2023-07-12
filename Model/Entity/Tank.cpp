#include "Tank.hpp"

using namespace models;

Tank::Tank(PoolTag ETag, std::string strName, AnimatedTexture *pTexture) : PoolableObject(ETag, strName, pTexture)
{
    this->bTopBounds = true;
    this->bLeftBounds = true;
    this->bBottomBounds = true;
    this->bRightBounds = true;
}

Tank::~Tank() {}

void Tank::initialize()
{
    this->centerSpriteOrigin();
}

void Tank::onActivate()
{
    // float fHalfWidth = this->pShip->getSprite()->getGlobalBounds().width / 2.0f;
    // float fSpacing = 9.0f;

    // this->pSprite->setPosition(this->pShip->getSprite()->getPosition().x + fHalfWidth + fSpacing,
    // this->pShip->getSprite()->getPosition().y);

    // this->pCollider->cleanCollisions();
    // this->pCollider->setCleanUp(false);
    // PhysicsManager::getInstance()->trackCollider(this->pCollider);
}

void Tank::onRelease() {}

PoolableObject *Tank::clone() {}

bool Tank::isTopBounds()
{
    return this->bTopBounds;
}

bool Tank::isLeftBounds()
{
    return this->bLeftBounds;
}

bool Tank::isBottomBounds()
{
    return this->bBottomBounds;
}

bool Tank::isRightBounds()
{
    return this->bRightBounds;
}

void Tank::onCollisionEnter(GameObject *pGameObject)
{
    if (pGameObject->getName().find("Border") != std::string::npos)
    {
        Collider *pCollider = (Collider *)this->findComponentByName(this->strName + " Collider");

        sf::Vector2f center1 = sf::Vector2f(pCollider->getGlobalBounds().left + pCollider->getGlobalBounds().width / 2, pCollider->getGlobalBounds().top + pCollider->getGlobalBounds().height / 2);
        sf::Vector2f center2 = sf::Vector2f(pGameObject->getGlobalBounds().left + pGameObject->getGlobalBounds().width / 2, pGameObject->getGlobalBounds().top + pGameObject->getGlobalBounds().height / 2);

        if (center1.x < center2.x)
        {
            this->bRightBounds = false;
        }
        if (center1.x > center2.x)
        {
            this->bLeftBounds = false;
        }
        if (center1.y < center2.y)
        {
            this->bBottomBounds = false;
        }
        if (center1.y > center2.y)
        {
            this->bTopBounds = false;
        }
        // this->bTopBounds = false;
        /*
        switch ((int)this->getSprite()->getRotation())
        {
        case 0:
            this->bTopBounds = false;
            break;
        case 180:
            this->bBottomBounds = false;
            break;
        case 270:
            this->bLeftBounds = false;
            break;
        case 90:
            this->bRightBounds = false;
            break;

        default:
            break;
        }
        */
        // this->bLeftBounds = false;
        // this->bBottomBounds = false;
        // this->bRightBounds = false;
    }

    // if(pGameObject->getName().find("Top Border") != std::string::npos) {
    //     this->bTopBounds = false;
    // }

    // if(pGameObject->getName().find("Left Border") != std::string::npos) {
    //     this->bLeftBounds = false;
    //     this->bBottomBounds = false;
    //     this->bRightBounds = false;
    // }

    // if(pGameObject->getName().find("Bottom Border") != std::string::npos) {
    //     this->bBottomBounds = false;
    //     this->bRightBounds = false;
    // }

    // if(pGameObject->getName().find("Right Border") != std::string::npos) {
    //     this->bRightBounds = false;
    // }
}

void Tank::onCollisionContinue(GameObject *pGameObject)
{
    this->onCollisionEnter(pGameObject);
    // if (pGameObject->getName().find("Border") != std::string::npos)
    // {
    //     switch ((int)this->getSprite()->getRotation())
    //     {
    //     case 0:
    //         this->bTopBounds = false;
    //         break;
    //     case 180:
    //         this->bBottomBounds = false;
    //         break;
    //     case 270:
    //         this->bLeftBounds = false;
    //         break;
    //     case 90:
    //         this->bRightBounds = false;
    //         break;

    //     default:
    //         break;
    //     }
    // }
    // if(pGameObject->getName().find("Top Border") != std::string::npos) {
    //     this->bTopBounds = false;
    // }

    // if(pGameObject->getName().find("Left Border") != std::string::npos) {
    //     this->bLeftBounds = false;
    // }

    // if(pGameObject->getName().find("Bottom Border") != std::string::npos) {
    //     this->bBottomBounds = false;
    // }

    // if(pGameObject->getName().find("Right Border") != std::string::npos) {
    //     this->bRightBounds = false;
    // }
}

void Tank::onCollisionExit(GameObject *pGameObject)
{
    if (pGameObject->getName().find("Border") != std::string::npos)
    {
        this->bTopBounds = true;
        this->bLeftBounds = true;
        this->bBottomBounds = true;
        this->bRightBounds = true;
    }

    // if(pGameObject->getName().find("Top Border") != std::string::npos) {
    //     this->bTopBounds = true;
    // }

    // if(pGameObject->getName().find("Left Border") != std::string::npos) {
    //     this->bLeftBounds = true;
    // }

    // if(pGameObject->getName().find("Bottom Border") != std::string::npos) {
    //     this->bBottomBounds = true;
    // }

    // if(pGameObject->getName().find("Right Border") != std::string::npos) {
    //     this->bRightBounds = true;
    // }
}

sf::RectangleShape *Tank::getRectangle()
{
    return this->pRectangle;
}

void Tank::moveBounds(float x, float y)
{
    this->CBounds = sf::FloatRect(this->CBounds.left + x, this->CBounds.top + y, this->CBounds.width, this->CBounds.height);
}