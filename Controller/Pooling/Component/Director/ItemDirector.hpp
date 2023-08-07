#ifndef DIRECTORS_ITEM_DIRECTOR_HPP
#define DIRECTORS_ITEM_DIRECTOR_HPP

#include "../../../../Config/Settings.hpp"

#include "../../../../Model/Enum/EnumAssetType.hpp"
#include "../../../../Model/Enum/EnumComponentType.hpp"
#include "../../../../Model/Enum/EnumPoolTag.hpp"

#include "../../../../Model/Component/Component.hpp"
#include "../../../../Model/Pooling/Item/Item.hpp"
#include "../../../../Model/AnimatedTexture.hpp"

#include "../../../Singleton/ObjectPoolManager.hpp"
#include "../../../Singleton/TextureManager.hpp"
#include "../../GameObjectPool.hpp"

#include "cstdlib"

namespace directors {
    using namespace controllers;
    using namespace components;

    class ItemDirector : public Component {
        private:
            float fSpawnInterval;
            float fTicks;

        public:
            ItemDirector(std::string strName);
            ~ItemDirector();

        private:
            void createItem(PoolTag ETag, int nPoolSize);
            void spawn();

        public:
            void perform();
    };
}

#endif