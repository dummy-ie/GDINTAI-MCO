#ifndef CONTROLLERS_GAME_HPP
#define CONTROLLERS_GAME_HPP

#include "../Config/Settings.hpp"

#include "Singleton/GameObjectManager.hpp"
#include "Singleton/TextureManager.hpp"
//#include "Singleton/SFXManager.hpp"
#include "Singleton/FontManager.hpp"
#include "System/SceneManager.hpp"

#include "../Model/Enum/EnumSceneTag.hpp"
#include "../Model/Scene/GameMenu.hpp"
#include "../Model/Scene/GameSpace.hpp"
namespace controllers {
    class Game {
        private:
            sf::RenderWindow rwWindow;

        public:
            Game();

        public:
            void run();
        
        private:
            void processEvents();
            void update(sf::Time tDeltaTime);
            void render();
    };
}

#endif