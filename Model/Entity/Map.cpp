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
   std::cout<<this->strName<<std::endl;
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
                /*for (size_t k = 0; k < 2; k++)
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
                }*/
                AssetType EType = AssetType::BRICK;
                AnimatedTexture *pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));

                Brick *pBrick = new Brick(
                    "Brick Wall", 
                    pTexture, 
                    sf::Vector2f(j * nOffset + 16, i * nOffset + 16)); 
                this->attachChild(pBrick);
                break;
            }
                // spawn a base at x = i * nOffset and y = j * nOffset
            case 4:
            {
                AssetType EType = AssetType::BASE;
                AnimatedTexture *pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));

                Base *pBase = new Base(
                    "Player Base", 
                    pTexture, 
                    sf::Vector2f(j * nOffset + 16, i * nOffset + 16),
                    TeamTag::PLAYER); 
                this->attachChild(pBase);
                this->vecPlayerBase.push_back(pBase);
                //std::cout << "created player base" << std::endl;
                break;
            }
                
            case 5:{
                AssetType EType = AssetType::BASE;
                AnimatedTexture *pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));

                Base *pBase = new Base(
                    "Enemy Base", 
                    pTexture, 
                    sf::Vector2f(j * nOffset + 16, i * nOffset + 16),
                    TeamTag::ENEMY); 
                this->attachChild(pBase);
                this->vecEnemyBase.push_back(pBase);
                //std::cout << "created enemy base" << std::endl;
                break;
            }
            default:
                break;
            }
        }
    }
}

// Map::~Map()
// {
// }

void Map::removeBase(Base* pBase){
    int nIndex = -1;
    if(pBase->getTeam() == TeamTag::PLAYER && !this->vecPlayerBase.empty()){
        for(int i = 0; i < this->vecPlayerBase.size(); i++){
            if(this->vecPlayerBase[i] == pBase){
                nIndex = i;
            }
        }
        if(nIndex != -1){
            this->vecPlayerBase.erase(this->vecPlayerBase.begin() + nIndex);
            std::cout<<"removed "<<nIndex<<" player base"<<std::endl;

            if (this->vecPlayerBase.empty() && ViewManager::getInstance()->getView(ViewTag::GAME_OVER_SCREEN) && !(ViewManager::getInstance()->getView(ViewTag::GAME_OVER_SCREEN)->isEnabled()))
            {
                ((GameOverScreen*)(ViewManager::getInstance()->getView(ViewTag::GAME_OVER_SCREEN)))->setGameStatus(1);
                ViewManager::getInstance()->getView(ViewTag::GAME_OVER_SCREEN)->setEnabled(true);
            }
                
        }
    }
    else if(!this->vecEnemyBase.empty()){
        for(int i = 0; i < this->vecEnemyBase.size(); i++){
            if(this->vecEnemyBase[i] == pBase){
                nIndex = i;
            }
        }
        if(nIndex != -1){
            this->vecEnemyBase.erase(this->vecEnemyBase.begin() + nIndex);
            std::cout<<"removed "<<nIndex<<" enemy base"<<std::endl;
            if (this->vecEnemyBase.empty() && ViewManager::getInstance()->getView(ViewTag::GAME_OVER_SCREEN) && !(ViewManager::getInstance()->getView(ViewTag::GAME_OVER_SCREEN)->isEnabled()))
            {
                ((GameOverScreen*)(ViewManager::getInstance()->getView(ViewTag::GAME_OVER_SCREEN)))->setGameStatus(0);
                ViewManager::getInstance()->getView(ViewTag::GAME_OVER_SCREEN)->setEnabled(true);
                ScoreView* pScoreView = NULL;
                int nScore = 0;
                if (ViewManager::getInstance()->getView(ViewTag::SCORE_VIEW))
                {
                    pScoreView = (ScoreView*)(ViewManager::getInstance()->getView(ViewTag::SCORE_VIEW));
                    nScore += pScoreView->nPlayerBaseKills;
                    nScore += pScoreView->nPlayerKills;
                }
        
                std::ofstream scores("File/scores.txt", std::ios::app);
                scores << nScore << std::endl;
                scores.close();
            }
        }
    }
}


std::vector<std::vector<int>> Map::getMap(){
    return this->vecMap;
}