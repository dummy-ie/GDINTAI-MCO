#ifndef CONTROLLERS_MAP_MANAGER_HPP
#define CONTROLLERS_MAP_MANAGER_HPP

namespace controllers {
    class MapManager {
        private:
            std::vector<std::vector<int>> vecMap;

        public:
            std::vector<int> getRandomTile(int nTile);
            std::vector<int> getClosestTile(float x, float y);
            std::vector<std::vector<int>> getMap();
            void setMap(std::vector<std::vector<int>> vecMap);
            void setMap(int x, int y, int value);

            bool isCentered(float x, float y, int nX, int nY, float range = 0);

        /* * * * * * * * * * * * * * * * * * * * * 
         *       SINGLETON-RELATED CONTENT       * 
         * * * * * * * * * * * * * * * * * * * * */
        private:
            static MapManager* P_SHARED_INSTANCE;

        private:
            MapManager();
            MapManager(const MapManager&);
            MapManager& operator = (const MapManager&);

        public:
            static MapManager* getInstance();
        /* * * * * * * * * * * * * * * * * * * * */
    };
}

#endif