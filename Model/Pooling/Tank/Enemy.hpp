#ifndef MODEL_ENEMY_HPP
#define MODEL_ENEMY_HPP

#include "../../Enum/EnumPoolTag.hpp"

#include "../../Component/Script/EnemyAI.hpp"
#include "../../Component/Script/Damager.hpp"

#include "../Tank Bullet/TankBullet.hpp"

#include "Tank.hpp"

namespace models {
    class Enemy : public Tank {
        protected:
            EnemyAI* pEnemyAIComponent;

        public:
            Enemy(PoolTag ETag, std::string strName, AnimatedTexture* pTexture);
            ~Enemy();

        public:
            void initialize();

        public:
            void onActivate();
            void onRelease();
            PoolableObject* clone();
    };
}

#endif