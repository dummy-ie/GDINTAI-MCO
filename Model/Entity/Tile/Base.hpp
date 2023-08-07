#ifndef MODELS_BASE_HPP
#define MODELS_BASE_HPP

#include "../Tile.hpp"

#include "../Border/Border.hpp"

#include "../../Enum/EnumTeamTag.hpp"

#include "../../Component/Script/Interface/Damageable.hpp"
#include "../../Component/Script/Damager.hpp"

#include "../Map.hpp"

namespace models {
    class Base : public Tile, public Damageable {
        private:
            sf::Color CColor;
            sf::RectangleShape* pRectangle;
            Damager* pDamagerComponent;
            TeamTag ETeam;
            
        public:
            Base(std::string strName, AnimatedTexture* pTexture, sf::Vector2f CPosition, TeamTag ETeam);
            ~Base();

        public:
            void initialize();

        public:
            void damage();
            void randomizePosition();

            TeamTag getTeam();
    };
}

#endif