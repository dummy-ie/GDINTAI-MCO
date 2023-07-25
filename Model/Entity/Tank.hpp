#ifndef MODELS_TANK_HPP
#define MODELS_TANK_HPP

#include "../Enum/EnumPoolTag.hpp"

#include "../Pooling/PoolableObject.hpp"

#include "../Component/Input/TankInput.hpp"
#include "../Component/Script/TankControls.hpp"
#include "../Component/Physics/Collider.hpp"

#include "../Component/Physics/Interface/CollisionListener.hpp"

namespace models {
    class Tank : public PoolableObject, public CollisionListener {
        protected:
            //std::vector<Base*> vecBase;
            sf::FloatRect COffset;
            sf::FloatRect CBounds;
            bool bTopBounds;
            bool bLeftBounds;
            bool bBottomBounds;
            bool bRightBounds;
            sf::RectangleShape* pRectangle;

        public:
            Tank(PoolTag ETag, std::string strName, AnimatedTexture* pTexture);
            ~Tank();

        public:
            void initialize();

        public:
            void onActivate();
            void onRelease();
            PoolableObject* clone();
        
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
    };
}

#endif