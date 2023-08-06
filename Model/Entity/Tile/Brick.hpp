#ifndef MODELS_BRICK_HPP
#define MODELS_BRICK_HPP

#include "../../../Config/Settings.hpp"

#include "../Tile.hpp"

#include "../Border/Border.hpp"

#include "../../Component/Script/Interface/Damageable.hpp"
#include "../../Component/Script/Damager.hpp"

namespace models {
    using namespace controllers;
    class Brick : public Tile, public Damageable {
        private:
            sf::Color CColor;
            sf::RectangleShape* pRectangle;
            Damager* pDamagerComponent;
        public:
            Brick(std::string strName, AnimatedTexture* pTexture, sf::Vector2f CPosition);
            ~Brick();

        public:
            void initialize();
        
        public:
            void damage();
    };
}

#endif