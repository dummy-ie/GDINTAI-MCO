#ifndef COMPONENTS_SPEEDER_HPP
#define COMPONENTS_SPEEDER_HPP

#include "../../Enum/EnumComponentType.hpp"

#include "../Component.hpp"

#include "Interface/Speedable.hpp"

namespace components {
    using namespace models;
    using namespace interfaces;
    class Speeder : public Component {
        private:
            Speedable* pSpeedable;
            bool bSpeed;
            float fTimer;
            float fTicks;
        
        public:
            Speeder(std::string strName);

        public:
            void perform();
            void start();
            void stop();

        private:
            void unspeed();

        public:
            void setSpeedable(Speedable* pDamageable);
    };
}

#endif