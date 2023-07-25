#ifndef MODEL_ENEMY_HPP
#define MODEL_ENEMY_HPP

#include "../../Enum/EnumPoolTag.hpp"
//#include "../../Component/Script/EnemyAI.hpp"

#include "../Tank.hpp"

namespace models {
    class Enemy : public Tank {
        public:
            Enemy(PoolTag ETag, std::string strName, AnimatedTexture* pTexture);
            ~Enemy();

        public:
            void initialize();
    };
}

#endif