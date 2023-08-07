#ifndef MODEL_PLAYER_HPP
#define MODEL_PLAYER_HPP

#include "../../Enum/EnumPoolTag.hpp"

#include "../../Component/Script/Damager.hpp"
#include "../../Component/Script/Interface/Damageable.hpp"

#include "../Tank Bullet/TankBullet.hpp"

#include "Tank.hpp"

namespace models {
    class Player : public Tank {
        public:
            bool isDead;

        public:
            Player(PoolTag ETag, std::string strName, AnimatedTexture* pTexture);
            ~Player();

        public:
            void initialize();
            void randomizePosition();

        public:
            void onActivate();
            void onRelease();
            PoolableObject* clone();
    };
}

#endif