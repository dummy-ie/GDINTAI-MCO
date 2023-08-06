#ifndef COMPONENTS_MOVER_HPP
#define COMPONENTS_MOVER_HPP

#include "../../Enum/EnumComponentType.hpp"

#include "../Component.hpp"

#include "Interface/Damageable.hpp"

namespace components {
    using namespace models;
    using namespace interfaces;
    class Damager : public Component {
        private:
            Damageable* pDamageable;
            bool bDamage;
            float fTicks;
        
        public:
            Damager(std::string strName);

        public:
            void perform();
            void start();
            void stop();

        private:
            void damage();

        public:
            void setDamageable(Damageable* pDamageable);
    };
}

#endif