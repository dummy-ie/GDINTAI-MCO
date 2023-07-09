#include "Map.hpp"

using namespace models;

Map::Map(std::vector<std::vector<int>> vecMap) : vecMap(vecMap)
{
    // limit the screen size to a square (in Game.cpp)
    
    /*
    Map is created with a 2D vector where the numbers
    in each slot represent what kind of tile there is
    (i.e., 0 is blank, 1 is a wall, 2 is a base, 3+ are powerups)
    
    as much as possible i wanna make it easy to implement something like
    an A* pathfinding algorithm for the bots which is why the input is a 2D array

    my idea is that the A* algorithm is run every frame and tells the bots
    which input to... input? 
    
    (ex., the A* function returns whichever direction is 
    the first step towards the target then the bot keeps 
    moving until the optimal direction is changed) 
    
    i might have to research how it's actually implemented in games tho lol

    The map is then iterated through and this class
    will spawn the corresponding tile on the screen 
    with specific offsets
    
    The tiles can be considered children of this gameobject?
    idk
    */

    int nOffset = 32; // pixel offset for the grid based on the sprite size for now

    // for (auto &vecRow : this->vecMap)
    for (size_t i = 0; i < this->vecMap.size(); i++)    
    {
        for (size_t j = 0; j < this->vecMap.at(0).size(); j++)    
        {
            switch (this->vecMap.at(i).at(j))
            {
                case 1:
                    // spawn a wall at x = i * nOffset and y = j * nOffset
                    break;
                case 2:
                    // spawn a base at x = i * nOffset and y = j * nOffset
                    break;
                default:
                    break;
            }
        }
    }
}

// Map::~Map()
// {
// }
