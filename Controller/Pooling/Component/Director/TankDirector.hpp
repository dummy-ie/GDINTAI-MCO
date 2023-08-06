#ifndef DIRECTORS_ENEMY_BUG_DIRECTOR_HPP
#define DIRECTORS_ENEMY_BUG_DIRECTOR_HPP

#include "../../../../Config/Settings.hpp"

#include "../../../../Model/Enum/EnumAssetType.hpp"
#include "../../../../Model/Enum/EnumComponentType.hpp"
#include "../../../../Model/Enum/EnumPoolTag.hpp"

#include "../../../../Model/Component/Component.hpp"
#include "../../../../Model/Pooling/Tank/Tank.hpp"
#include "../../../../Model/AnimatedTexture.hpp"

#include "../../../Singleton/ObjectPoolManager.hpp"
#include "../../../Singleton/TextureManager.hpp"
#include "../../GameObjectPool.hpp"

#include "cstdlib"

namespace directors {
    using namespace controllers;
    using namespace components;

    class TankDirector : public Component {
        private:
            float fSpawnInterval;
            float fTicks;

        public:
            TankDirector(std::string strName);
            ~TankDirector();

        private:
            void createPlayer(PoolTag ETag, int nPoolSize);
            void createEnemy(PoolTag ETag, int nPoolSize);
            void spawn();

        public:
            void perform();
    };
}

#endif