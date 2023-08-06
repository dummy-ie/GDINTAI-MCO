#ifndef MODELS_ITEM_HPP
#define MODELS_ITEM_HPP

#include "../../Enum/EnumPoolTag.hpp"
#include "../../Enum/EnumItemType.hpp"

#include "../../AnimatedTexture.hpp"
#include "../../GameObject.hpp"

#include "../../Component/Renderer/Renderer.hpp"
#include "../../Component/Physics/Collider.hpp"

#include "../Tank/Tank.hpp"

#include "../PoolableObject.hpp"

#include "../../../Controller/Singleton/ObjectPoolManager.hpp"
#include "../../../Controller/System/PhysicsManager.hpp"

namespace models {
    class Tank;
    class Player;
    class Enemy;
}

namespace models {
    using namespace components;
    using namespace listeners;
    using namespace systems;

    class Item : public PoolableObject, public CollisionListener {
        private:
            ItemType EType;
            Collider* pCollider;

        public:
            Item(PoolTag ETag, std::string strName, AnimatedTexture* pTexture);

        public:
            void initialize();
            void randomizeType();

            void onActivate();
            void onRelease();

            void onCollisionEnter(GameObject* pGameObject);
            void onCollisionContinue(GameObject* pGameObject);
            void onCollisionExit(GameObject* pGameObject);

            ItemType getType();

            PoolableObject* clone();
    };
}

#endif