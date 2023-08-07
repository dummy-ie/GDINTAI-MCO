#ifndef MODELS_BASE_HPP
#define MODELS_BASE_HPP

#include "../Tile.hpp"

#include "../Border/Border.hpp"

#include "../../Component/Script/Interface/Damageable.hpp"
#include "../../Component/Script/Damager.hpp"

namespace models {
    class Base : public Tile, public Damageable {
        private:
            sf::Color CColor;
            sf::RectangleShape* pRectangle;
            Damager* pDamagerComponent;
            
        public:
            Base(std::string strName, AnimatedTexture* pTexture);
            ~Base();

        public:
            void initialize();

        public:
            void damage();
    };
}

#endif