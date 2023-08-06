#ifndef MODELS_TANK_BULLET_HPP
#define MODELS_TANK_BULLET_HPP

#include "../../Enum/EnumPoolTag.hpp"

#include "../../AnimatedTexture.hpp"
#include "../../GameObject.hpp"

#include "../../Component/Script/TankBulletMovement.hpp"
#include "../../Component/Script/TankBulletExplode.hpp"
#include "../../Component/Renderer/Renderer.hpp"
#include "../../Component/Physics/Collider.hpp"

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

    class TankBullet : public PoolableObject, public CollisionListener {
        private:
            Tank* pTank;
            TankBulletExplode* pExplodeComponent;
            TankBulletMovement* pMovementComponent;
            Collider* pCollider;

        public:
            TankBullet(PoolTag ETag, std::string strName, AnimatedTexture* pTexture, Tank* pTank);

        public:
            void initialize();
            void onActivate();
            void onRelease();

            void onCollisionEnter(GameObject* pGameObject);
            void onCollisionContinue(GameObject* pGameObject);
            void onCollisionExit(GameObject* pGameObject);

            PoolableObject* clone();
    };
}

#endif