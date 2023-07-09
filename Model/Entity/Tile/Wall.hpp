#ifndef MODELS_WALL_HPP
#define MODELS_WALL_HPP

#include "../Tile.hpp"

namespace models {
    class Wall : public Tile {
        public:
            Wall(std::string strName, AnimatedTexture* pTexture);
            ~Wall();

        public:
            void initialize();
    };
}

#endif