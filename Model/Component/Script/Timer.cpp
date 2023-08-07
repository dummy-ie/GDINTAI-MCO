#include "Timer.hpp"

using namespace components;

Timer::Timer(std::string strName) : Component(strName, ComponentType::SCRIPT)
{
    this->fTicks = 120.0f;
}

void Timer::perform()
{
    if (this->fTicks > 0.f)
        this->fTicks -= this->tDeltaTime.asSeconds();

    this->fUpdateTicks += this->tDeltaTime.asSeconds();
    if (this->fUpdateTicks >= this->fUpdateInterval)
    {
        this->fUpdateTicks = 0.0f;
        if (this->bIsCounting)
        {
            this->pTimeable->setTime(this->fTicks);
        }
        // this->pTimeable->update();
    }
}

/*void Timer::switchView() {
    if(this->pSwitchable == NULL) {
        std::cout << "[ERROR] : One or more dependencies are missing." << std::endl;
    }
    else {
        this->pSwitchable->switchView();
    }
}*/

void Timer::reset()
{
    this->bIsCounting = true;
    this->fTicks = 120.0f;
    // this->fUpdateTicks = 0.0f;
}

void Timer::stop()
{
    this->bIsCounting = false;
}

void Timer::setTimeable(Timeable *pTimeable)
{
    this->pTimeable = pTimeable;
}

float components::Timer::getTime()
{
    return fTicks;
}
