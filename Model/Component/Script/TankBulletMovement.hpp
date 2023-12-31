#ifndef COMPONENTS_TANK_BULLET_MOVEMENT_HPP
#define COMPONENTS_TANK_BULLET_MOVEMENT_HPP

#include "../../Entity/Map.hpp"
#include "../../../Config/Settings.hpp"
#include "../../Enum/EnumComponentType.hpp"
#include "../../Pooling/PoolableObject.hpp"
#include "../Component.hpp"
#include "../Physics/Collider.hpp"

namespace components {
    using namespace models;

    class TankBulletMovement : public Component {
        private:
            bool bMoving;
            float fFrameInterval;
            float fTicks;
            float fSpeed;

        public:
            TankBulletMovement(std::string strName);

        public:
            void perform();
            void start();
            void stop();
    };
}

#endif