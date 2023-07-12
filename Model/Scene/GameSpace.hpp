#ifndef SCENES_GAME_SPACE_HPP
#define SCENES_GAME_SPACE_HPP

#include "../Scene.hpp"

#include "../../Config/Settings.hpp"

#include "../Enum/EnumAssetType.hpp"
#include "../Enum/EnumSceneTag.hpp"

#include "../AnimatedTexture.hpp"
#include "../EmptyGameObject.hpp"

#include "../Entity/Background.hpp"
#include "../Entity/Map.hpp"

#include "../Entity/Tank/Player.hpp"
#include "../Entity/Tank/Enemy.hpp"

#include "../Entity/Tile/Wall.hpp"

#include "../Pooling/Tank Bullet/TankBullet.hpp"

namespace scenes {
    using namespace controllers;
    using namespace models;
    using namespace views;
    using namespace systems;
    class GameSpace : public Scene {
        public:
            GameSpace();
            ~GameSpace();

        public:
            void onLoadResources();
            void onLoadObjects();
            void onUnloadResources();

        private:
            void createNullObjectComponents();
            void createObjectPools();
            void createMap();
            void createTanks();
            void createBorders();
    };
}

#endif