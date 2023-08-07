#ifndef VIEWS_SCORE_VIEW_HPP
#define VIEWS_SCORE_VIEW_HPP

#include "../View.hpp"
#include "../Text.hpp"

#include "../../Controller/System/ViewManager.hpp"
#include "../../Controller/Singleton/FontManager.hpp"

namespace views {
    using namespace controllers;
    using namespace systems;
    class ScoreView : public View {
        private:
            int nPlayerKills;
            int nPlayerBaseKills;
            int nEnemyKills;
            int nEnemyBaseKills;
            Text* txtPlayerKill;
            Text* txtPlayerBase;
            Text* txtEnemyKill;
            Text* txtEnemyBase;

        public:
            ScoreView(std::string strName);
            ~ScoreView();

        public:
            void initialize();

        public:
            void incrementPlayerKill();
            void incrementPlayerBaseKill();
            void incrementEnemyKill();
            void incrementEnemyBaseKill();

    };
}

#endif