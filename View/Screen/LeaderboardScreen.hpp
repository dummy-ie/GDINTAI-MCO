#ifndef VIEWS_LEADERBOARD_SCREEN_HPP
#define VIEWS_LEADERBOARD_SCREEN_HPP

#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "../View.hpp"
#include "../Text.hpp"
#include "../Button.hpp"

#include "../Interface/ButtonListener.hpp"

#include "../../Model/Enum/EnumFontType.hpp"
#include "../../Model/Enum/EnumViewTag.hpp"

// #include "GameSpaceUI/Parts/GameTimer.hpp"
#include "../../Controller/Singleton/FontManager.hpp"
#include "../../Controller/System/ViewManager.hpp"
#include "../../Controller/System/SceneManager.hpp"

namespace views {
    using namespace systems;
    class LeaderboardScreen : public View, public ButtonListener {
        private:
            std::vector<Text*> vecScores;
            // std::vector<std::vector<Text*>> vecTime;
            // std::vector<GameTimer*> vecTopTimes;
            Text* pReturn;

        public:
            LeaderboardScreen(std::string strName);
            ~LeaderboardScreen();

        public:
            void initialize();
            
        public:
            // Text* copyText(Text* pReference, std::string strText, float fScale);
            void loadScores();

            void onClick(Button* pButton);
            void onHover(Button* pButton);
            void onRelease(Button* pButton);
            void reset(Button* pButton);
    };
}

#endif