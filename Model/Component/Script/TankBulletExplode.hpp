#ifndef COMPONENTS_TANK_BULLET_EXPLODE_HPP
#define COMPONENTS_TANK_BULLET_EXPLODE_HPP

#include "../../../Config/Settings.hpp"
#include "../../Enum/EnumComponentType.hpp"
#include "../../Pooling/PoolableObject.hpp"
#include "../Component.hpp"
#include "../Physics/Collider.hpp"

namespace components {
    using namespace models;

    class TankBulletExplode : public Component {
        private:
            bool bExploding;
            float fFrameInterval;
            float fTicks;

        public:
            TankBulletExplode(std::string strName);

        public:
            void perform();
            void start();
            void stop();
    };
}

#endif