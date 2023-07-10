#ifndef MODELS_WALL_HPP
#define MODELS_WALL_HPP

#include "../Tile.hpp"

#include "../Border/Border.hpp"

namespace models {
    class Wall : public Tile {
        private:
            // sf::Vector2f vecBlockPart;
        
        public:
            // Wall(std::string strName, AnimatedTexture* pTexture, sf::Vector2f CPosition, sf::Vector2f vecBlockPart = sf::Vector2f(-1, -1));
            Wall(std::string strName, AnimatedTexture* pTexture, sf::Vector2f CPosition);
            ~Wall();

        public:
            void initialize();
    };
}

#endif