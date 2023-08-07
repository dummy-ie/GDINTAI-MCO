#include "Speeder.hpp"

using namespace components;

Speeder::Speeder(std::string strName) : Component(strName, ComponentType::SCRIPT) {
    this->fTicks = 0.0f;
    this->fTimer = 0.0f;
    this->bSpeed = false;
}

void Speeder::perform() {
    float fFrameInterval = 1.f;

    if (this->bSpeed) {
        this->fTicks += this->tDeltaTime.asSeconds();
        if (this->fTicks >= fFrameInterval) {
            this->fTicks = 0.0f;
            this->fTimer -= 1.f;
            if(this->fTimer < 0.f){
                this->fTimer = 0.f;
                this->unspeed();
            }
        }
    }
}

void Speeder::start() {
    this->fTimer = 10.f;
    this->bSpeed = true;
}

void Speeder::stop() {
    this->bSpeed = false;
    this->unspeed();
}

void Speeder::unspeed(){
    this->pSpeedable->unspeed();
}

void Speeder::setSpeedable(Speedable* pSpeedable) {
    this->pSpeedable = pSpeedable;
}