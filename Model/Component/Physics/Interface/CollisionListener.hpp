#ifndef LISTENERS_COLLISION_LISTENER_HPP
#define LISTENERS_COLLISION_LISTENER_HPP

#include "../../../GameObject.hpp"

namespace listeners {
    using namespace models;
    
    class CollisionListener {
        public:
            ~CollisionListener() {}

        public:
            virtual void onCollisionEnter(GameObject* pGameObject) = 0;
            virtual void onCollisionContinue(GameObject* pGameObject) = 0;
            virtual void onCollisionExit(GameObject* pGameObject) = 0;
    };
}

#endif