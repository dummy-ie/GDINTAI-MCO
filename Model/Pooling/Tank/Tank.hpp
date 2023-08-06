#ifndef MODELS_TANK_HPP
#define MODELS_TANK_HPP

#include "../../Enum/EnumPoolTag.hpp"

#include "../PoolableObject.hpp"

#include "../../Component/Input/TankInput.hpp"
#include "../../Component/Script/TankControls.hpp"
#include "../../Component/Script/Killable.hpp"
#include "../../Component/Physics/Collider.hpp"

#include "../../Component/Script/Interface/Damageable.hpp"

#include "../../Component/Physics/Interface/CollisionListener.hpp"

namespace models {
    using namespace components;
    using namespace interfaces;
    class Tank : public PoolableObject, public CollisionListener, public Damageable {
        protected:
            //std::vector<Base*> vecBase;
            sf::FloatRect COffset;
            sf::FloatRect CBounds;
            sf::Vector2f vecSpawn = sf::Vector2f(0.0f, 0.0f);
            bool bTopBounds;
            bool bLeftBounds;
            bool bBottomBounds;
            bool bRightBounds;
            sf::RectangleShape* pRectangle;
            Killable* pKillableComponent;
            Damager* pDamagerComponent;

        public:
            Tank(PoolTag ETag, std::string strName, AnimatedTexture* pTexture);
            ~Tank();

        public:
            void initialize();

        public:
            virtual void onActivate() = 0;
            virtual void onRelease() = 0;
            virtual PoolableObject* clone() = 0;
        
        public:
            bool isTopBounds();
            bool isLeftBounds();
            bool isBottomBounds();
            bool isRightBounds();

        public:
            virtual void onCollisionEnter(GameObject* pGameObject);
            virtual void onCollisionContinue(GameObject* pGameObject);
            virtual void onCollisionExit(GameObject* pGameObject);

        public:
            sf::RectangleShape* getRectangle();
            sf::FloatRect getGlobalBounds();
            void moveBounds(float x, float y);

        public:
            virtual void damage();
    };
}

#endif