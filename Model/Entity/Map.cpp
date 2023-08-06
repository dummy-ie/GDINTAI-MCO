#include "Map.hpp"

using namespace models;

Map::Map(std::vector<std::vector<int>> vecMap) : GameObject("Map"), vecMap(vecMap)
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
}

void Map::initialize()
{
    int nOffset = 32; // pixel offset for the grid based on the sprite size for now

    // for (auto &vecRow : this->vecMap)
    for (size_t i = 0; i < this->vecMap.size(); i++)
    {
        for (size_t j = 0; j < this->vecMap.at(0).size(); j++)
        {
            switch (this->vecMap.at(i).at(j))
            {
            case 1:
            {
                // for (size_t k = 0; k < 2; k++)
                // {
                //     for (size_t l = 0; l < 2; l++)
                //     {
                        AssetType EType = AssetType::STONE;
                        AnimatedTexture *pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));

                        Wall *pWall = new Wall(
                            "Stone Wall", 
                            pTexture, 
                            sf::Vector2f(j * nOffset + 16, i * nOffset + 16)); 
                        this->attachChild(pWall);
                //     }
                // }

                break;
            }
                // Wall* pWall = new Wall("Stone Wall", pTexture, sf::Vector2f(i * nOffset, j * nOffset));
                // spawn a wall at x = i * nOffset and y = j * nOffset
            case 2:
            {
                for (size_t k = 0; k < 2; k++)
                {
                    for (size_t l = 0; l < 2; l++)
                    {
                        AssetType EType = AssetType::BRICK;
                        AnimatedTexture *pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));

                        Brick *pBrick = new Brick(
                            "Brick Wall", 
                            pTexture, 
                            sf::Vector2f(j * nOffset + k * 16 + 8, i * nOffset + l * 16 + 8)); 
                        this->attachChild(pBrick);
                        // std::cout << "created a wall" << std::endl;
                    }
                }

                break;
            }
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


std::vector<std::vector<int>> Map::getMap(){
    return this->vecMap;
}