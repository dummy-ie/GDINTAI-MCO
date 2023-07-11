#ifndef MODEL_PLAYER_HPP
#define MODEL_PLAYER_HPP

#include "../../Enum/EnumPoolTag.hpp"

#include "../Tank.hpp"

namespace models {
    class Player : public Tank {
        public:
            sf::RectangleShape* pRectangle;

        private:
            sf::FloatRect COffset;
            
        public:
            Player(PoolTag ETag, std::string strName, AnimatedTexture* pTexture);
            ~Player();

        public:
            void initialize();
    };
}

#endif