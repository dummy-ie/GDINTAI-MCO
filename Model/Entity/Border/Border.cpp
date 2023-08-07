#include "Border.hpp"

using namespace models;

Border::Border(std::string strName, sf::FloatRect CBounds) : GameObject(strName, NULL) {
    this->CBounds = CBounds;
}

Border::~Border() {}

void Border::initialize() {
    this->pCollider = new Collider(this->strName + " Collider");
    this->pCollider->setListener(this);

    this->attachComponent(this->pCollider);
    //std::cout << this->strName << " ColliderLoc " << pCollider->getGlobalBounds().left << " x " << this->getGlobalBounds().top << std::endl;
    //std::cout << this->strName << " Collider " << pCollider->getGlobalBounds().width << " x " << this->getGlobalBounds().height << std::endl;
    PhysicsManager::getInstance()->trackCollider(this->pCollider);
}

void Border::onCollisionEnter(GameObject* pGameObject) {
    // std::cout << "[BORDER] : ENTER" << std::endl;
    std::cout << this->getName() << std::endl;
    std::cout << pGameObject->getName() << std::endl;
    if (this->getName().find("Brick") != std::string::npos 
    && pGameObject->getName().find("Bullet") != std::string::npos)
    {
        std::cout << "bullet hit a brick wall" << std::endl;
        PhysicsManager::getInstance()->untrackCollider(this->pCollider);
        PhysicsManager::getInstance()->cleanUp();
        ((Damager*)this->getParent()->findComponentByName(this->getParent()->getName() + " Damager"))->start();
    }
    if (this->getName().find("Based") != std::string::npos 
    && pGameObject->getName().find("Bullet") != std::string::npos)
    {
        std::cout << "bullet hit a base" << std::endl;
        PhysicsManager::getInstance()->untrackCollider(this->pCollider);
        PhysicsManager::getInstance()->cleanUp();
        ((Damager*)this->getParent()->findComponentByName(this->getParent()->getName() + " Damager"))->start();
    }
}

void Border::onCollisionContinue(GameObject* pGameObject) {
    //std::cout << "[BORDER] : CONTINUE" << std::endl;
}

void Border::onCollisionExit(GameObject* pGameObject) {
    // std::cout << "[BORDER] : EXIT" << std::endl;
}

sf::FloatRect Border::getGlobalBounds() {
    return this->CBounds;
}