#ifndef MODEL_TILE_HPP
#define MODEL_TILE_HPP

#include "../GameObject.hpp"

namespace models {
    class Tile : public GameObject {
        public:
            Tile(std::string strName, AnimatedTexture* pTexture);
            ~Tile();
    };
}

#endif