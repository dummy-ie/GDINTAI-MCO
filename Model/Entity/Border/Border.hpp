#ifndef MODELS_BORDER_HPP
#define MODELS_BORDER_HPP

#include "../../GameObject.hpp"
#include "../../Component/Component.hpp"
#include "../../Component/Physics/Collider.hpp"
#include "../../Component/Physics/Interface/CollisionListener.hpp"

#include "../../../Controller/System/PhysicsManager.hpp"

namespace models {
    using namespace components;
    using namespace listeners;
    using namespace systems;
    
    class Border : public GameObject, public CollisionListener {
        private:
            sf::FloatRect CBounds;

        public:
            Border(std::string strName, sf::FloatRect CBounds);
            ~Border();

        public:
            void initialize();
            void onCollisionEnter(GameObject* pGameObject);
            void onCollisionExit(GameObject* pGameObject);

        public:
            sf::FloatRect getGlobalBounds();
    };
}

#endif