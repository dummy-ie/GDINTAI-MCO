#include "Border.hpp"

using namespace models;

Border::Border(std::string strName, sf::FloatRect CBounds) : GameObject(strName, NULL) {
    this->CBounds = CBounds;
}

Border::~Border() {}

void Border::initialize() {
    Collider* pCollider = new Collider(this->strName + " Collider");
    pCollider->setListener(this);

    this->attachComponent(pCollider);
    //std::cout << this->strName << " ColliderLoc " << pCollider->getGlobalBounds().left << " x " << this->getGlobalBounds().top << std::endl;
    //std::cout << this->strName << " Collider " << pCollider->getGlobalBounds().width << " x " << this->getGlobalBounds().height << std::endl;
    PhysicsManager::getInstance()->trackCollider(pCollider);
}

void Border::onCollisionEnter(GameObject* pGameObject) {
    std::cout << "[BORDER] : ENTER" << std::endl;
}

void Border::onCollisionContinue(GameObject* pGameObject) {
    //std::cout << "[BORDER] : CONTINUE" << std::endl;
}

void Border::onCollisionExit(GameObject* pGameObject) {
    std::cout << "[BORDER] : EXIT" << std::endl;
}

sf::FloatRect Border::getGlobalBounds() {
    return this->CBounds;
}