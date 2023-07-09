#ifndef MODELS_TILE_HPP
#define MODELS_TILE_HPP

#include "../GameObject.hpp"

namespace models {
    class Tile : public GameObject {
        protected:
            sf::FloatRect CBounds;
        
        public:
            Tile(std::string strName, AnimatedTexture* pTexture);
            ~Tile();

        public:
            void initialize();
    };
}

#endif