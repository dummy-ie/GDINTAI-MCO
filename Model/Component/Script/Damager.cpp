#include "Damager.hpp"

using namespace components;

Damager::Damager(std::string strName) : Component(strName, ComponentType::SCRIPT) {
    this->fTicks = 0.0f;
    this->bDamage = false;
}

void Damager::perform() {
    float fFrameInterval = 0.01f;

    if (this->bDamage) {
        this->fTicks += this->tDeltaTime.asSeconds();
        if (this->fTicks >= fFrameInterval) {
            this->fTicks = 0.0f;
            this->damage();
        }
    }
}

void Damager::start() {
    this->bDamage = true;
}

void Damager::stop() {
    this->bDamage = false;
}

void Damager::damage() {
    if(this->pDamageable == NULL) {
        std::cout << "[ERROR] : One or more dependencies are missing." << std::endl;
    }
    else {
        this->pDamageable->damage();
    }
}

void Damager::setDamageable(Damageable* pDamageable) {
    this->pDamageable = pDamageable;
}