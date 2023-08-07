#ifndef SCENES_GAME_MENU_HPP
#define SCENES_GAME_MENU_HPP

#include "../Scene.hpp"

#include "../../Config/Settings.hpp"

#include "../../Controller/Singleton/TextureManager.hpp"

#include "../Enum/EnumAssetType.hpp"
#include "../Enum/EnumSceneTag.hpp"

#include "../AnimatedTexture.hpp"

#include "../Entity/Background.hpp"

#include "../../View/Screen/TitleScreen.hpp"
#include "../../View/Screen/MapSelectionScreen.hpp"
#include "../../View/Screen/LeaderboardScreen.hpp"

namespace scenes {
    using namespace models;
    using namespace views;
    class GameMenu : public Scene {
        public:
            GameMenu();
            ~GameMenu();

        public:
            void onLoadResources();
            void onLoadObjects();
            void onUnloadResources();

        private:
            void createMenuInterface();
            void createMapSelectionInterface();
            void createLeaderboardInterface();
            void createBackground();
    };
}

#endif