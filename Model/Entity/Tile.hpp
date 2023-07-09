#ifndef MODELS_TILE_HPP
#define MODELS_TILE_HPP

#include "../GameObject.hpp"

namespace models {
    class Tile : public GameObject {
        protected:
            sf::Vector2f CPosition;

        public:
            Tile(std::string strName, AnimatedTexture* pTexture, sf::Vector2f CPosition);
            ~Tile();

        public:
            void initialize();
    };
}

#endif