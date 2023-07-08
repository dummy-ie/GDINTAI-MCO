#ifndef COMPONENTS_TANK_CONTROLS_HPP
#define COMPONENTS_TANK_CONTROLS_HPP

#include "../../Entity/Tank.hpp"

#include "../Component.hpp"
#include "../Input/TankInput.hpp"

#include "../../Enum/EnumComponentType.hpp"
#include "../../Enum/EnumPoolTag.hpp"

#include "../../../Controller/Singleton/ObjectPoolManager.hpp"

namespace components {
    using namespace controllers;

    class TankControls : public Component {
        private:
            float fSpeed;
            
        public:
            TankControls(std::string strName);

        public:
            void perform();
    };
}

#endif