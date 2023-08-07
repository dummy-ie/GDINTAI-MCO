#include "MapManager.hpp"

using namespace controllers;

std::vector<int> MapManager::getRandomTile(int nTile){
    int nRow = this->vecMap.size();
    int nCol = (nRow > 0) ? this->vecMap[0].size() : 0;
    if(nRow == 0){
        return {-1,-1};
    }

    std::vector<std::vector<int>> vecPositions;
    for (int i = 0; i < nRow; ++i) {
        for (int j = 0; j < nCol; ++j) {
            if (this->vecMap[i][j] == nTile) {
                vecPositions.push_back({j, i});
            }
        }
    }

    if(vecPositions.empty()){
        return {-1,-1};
    }

    int nRand = std::rand() % vecPositions.size();
    return vecPositions[nRand];
}

std::vector<std::vector<int>> MapManager::getAllTile(int nTile){
    int nRow = this->vecMap.size();
    int nCol = (nRow > 0) ? this->vecMap[0].size() : 0;
    if(nRow == 0){
        return {};
    }

    std::vector<std::vector<int>> vecPositions;
    for (int i = 0; i < nRow; ++i) {
        for (int j = 0; j < nCol; ++j) {
            if (this->vecMap[i][j] == nTile) {
                vecPositions.push_back({j, i});
            }
        }
    }

    if(vecPositions.empty()){
        return {};
    }

    return vecPositions;
}
//get nearest tile from screen coordinates, doesnt clamp values so beware of out of bounds
std::vector<int> MapManager::getClosestTile(float x, float y){
    float tileCenterX, tileCenterY;

    //each tile be 32 pixels wide, please dont change
    int nX = x / 32;
    int nY = y / 32;

    std::vector<int> vecLocation = {nX,nY};

    return vecLocation;
}

std::vector<std::vector<int>> MapManager::getMap() {
    return this->vecMap;
}

void MapManager::setMap(std::vector<std::vector<int>> vecMap) {
    this->vecMap = vecMap;
}

void MapManager::setMap(int x, int y, int value){
    this->vecMap[y][x] = value;
}

bool MapManager::isCentered(float x, float y, int nX, int nY, float range){
    float tileCenterX, tileCenterY;

    float dist;

    float tileSize = 32.f;

    int nRow = this->vecMap.size();
    int nCol = (nRow > 0) ? this->vecMap[0].size() : 0;

    auto distance = [](int x1, int y1, int x2, int y2) {
        return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    };

    bool inRange = false;

    //down
    if(nY + 1 < nRow && !inRange){
        tileCenterX = (nX * tileSize) + (tileSize / 2);
        tileCenterY = ((nY + 1) * tileSize) + (tileSize / 2);
        inRange = (distance(x,y,tileCenterX,tileCenterY) <= range);
    }
    //up
    if(nY - 1 >= 0 && !inRange){
        tileCenterX = (nX * tileSize) + (tileSize / 2);
        tileCenterY = ((nY - 1) * tileSize) + (tileSize / 2);
        inRange = (distance(x,y,tileCenterX,tileCenterY) <= range);
    }
    //right
    if(nX + 1 < nCol && !inRange){
        tileCenterX = ((nX + 1) * tileSize) + (tileSize / 2);
        tileCenterY = (nY * tileSize) + (tileSize / 2);
        inRange = (distance(x,y,tileCenterX,tileCenterY) <= range);
    }
    //left
    if(nX - 1 >= 0 && !inRange){
        tileCenterX = ((nX - 1) * tileSize) + (tileSize / 2);
        tileCenterY = (nY * tileSize) + (tileSize / 2);
        inRange = (distance(x,y,tileCenterX,tileCenterY) <= range);
    }

    return inRange;
}

/* * * * * * * * * * * * * * * * * * * * * 
 *       SINGLETON-RELATED CONTENT       * 
 * * * * * * * * * * * * * * * * * * * * */
MapManager* MapManager::P_SHARED_INSTANCE = NULL;
MapManager::MapManager() {}
MapManager::MapManager(const MapManager&) {}

MapManager* MapManager::getInstance() {
    if(P_SHARED_INSTANCE == NULL)
        P_SHARED_INSTANCE = new MapManager();

    return P_SHARED_INSTANCE;
}
/* * * * * * * * * * * * * * * * * * * * */
