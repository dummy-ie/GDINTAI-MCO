#ifndef MODELS_BASE_HPP
#define MODELS_BASE_HPP

#include "../Tile.hpp"

namespace models {
    class Base : public Tile {
        public:
            Base(std::string strName, AnimatedTexture* pTexture);
            ~Base();
    };
}

#endif