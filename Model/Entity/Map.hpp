#ifndef MODELS_MAP_HPP
#define MODELS_MAP_HPP

#include <vector>

namespace models {
    class Map : public GameObject
    {
    private:
        std::vector<std::vector<int>> vecMap;
    public:
        Map(std::vector<std::vector<int>> vecMap);
        // ~Map();
    };   
}

#endif