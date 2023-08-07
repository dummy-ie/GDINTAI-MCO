#ifndef MODELS_MAP_HPP
#define MODELS_MAP_HPP

#include <vector>
#include "../GameObject.hpp"
#include "../Enum/EnumAssetType.hpp"
#include "../Enum/EnumSceneTag.hpp"

#include "../AnimatedTexture.hpp"
#include "../EmptyGameObject.hpp"

#include "Tile/Wall.hpp"
#include "Tile/Brick.hpp"
#include "Tile/Base.hpp"

namespace models {
    class Map : public GameObject
    {
    private:
        std::vector<std::vector<int>> vecMap;
    public:
        Map(std::vector<std::vector<int>> vecMap);
        void initialize();
        // ~Map();

    public:
        std::vector<std::vector<int>> getMap();
    };   
}

#endif