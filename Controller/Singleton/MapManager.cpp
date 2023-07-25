#include "MapManager.hpp"

using namespace controllers;

//get nearest tile from screen coordinates, doesnt clamp values so beware of out of bounds
std::vector<int> MapManager::getClosestTile(float x, float y){
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
    this->vecMap[x][y] = value;
}

bool MapManager::isKindaCentered(float x, float y, int nX, int nY){
    float range = 1.0;

    float tileCenterX, tileCenterY;

    float dist;

    int nRow = this->vecMap.size();
    int nCol = (nRow > 0) ? this->vecMap[0].size() : 0;

    //down
    if(nY + 1 < nRow){
        
    }
    //up
    if(nY - 1 > 0){

    }
    //right
    if(nX + 1 < nCol){

    }
    //left
    if(nX - 1 > 0){

    }


    bool inRange;
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
