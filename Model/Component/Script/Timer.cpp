#include "Timer.hpp"

using namespace components;

Timer::Timer(std::string strName) : Component(strName, ComponentType::SCRIPT)
{
    this->fTicks = 120.0f;
}

void Timer::perform()
{
    if (this->fTicks > 0.f)
        this->fTicks -= this->tDeltaTime.asSeconds();

    this->fUpdateTicks += this->tDeltaTime.asSeconds();
    if (this->fUpdateTicks >= this->fUpdateInterval)
    {
        this->fUpdateTicks = 0.0f;
        if (this->bIsCounting)
        {
            this->pTimeable->setTime(this->fTicks);
            if (this->fTicks <= 0.f && ViewManager::getInstance()->getView(ViewTag::GAME_OVER_SCREEN))
            {
                GameOverScreen *pGameOverScreen = (GameOverScreen *)(ViewManager::getInstance()->getView(ViewTag::GAME_OVER_SCREEN));
                pGameOverScreen->setEnabled(true);
                this->stop();

                ScoreView *pScoreView = NULL;
                int nScore = 0;
                if (ViewManager::getInstance()->getView(ViewTag::SCORE_VIEW))
                {
                    pScoreView = (ScoreView *)(ViewManager::getInstance()->getView(ViewTag::SCORE_VIEW));
                    if (pScoreView->nPlayerBaseKills > pScoreView->nEnemyBaseKills)
                    {
                        pGameOverScreen->setGameStatus(0);
                        nScore += pScoreView->nPlayerBaseKills;
                        nScore += pScoreView->nPlayerKills;
                    }
                    else if (pScoreView->nPlayerBaseKills < pScoreView->nEnemyBaseKills)
                        pGameOverScreen->setGameStatus(1);
                    else if (pScoreView->nPlayerBaseKills == pScoreView->nEnemyBaseKills)
                    {
                        if (pScoreView->nPlayerKills > pScoreView->nEnemyKills)
                        {
                            pGameOverScreen->setGameStatus(0);
                            nScore += pScoreView->nPlayerBaseKills;
                            nScore += pScoreView->nPlayerKills;
                        }
                        else if (pScoreView->nPlayerKills < pScoreView->nEnemyKills)
                            pGameOverScreen->setGameStatus(1);
                        else if (pScoreView->nPlayerKills == pScoreView->nEnemyKills)
                            pGameOverScreen->setGameStatus(2);
                    }
                }

                std::ofstream scores("File/scores.txt", std::ios::app);
                scores << nScore << std::endl;
                scores.close();
            }

            if (ViewManager::getInstance()->getView(ViewTag::GAME_OVER_SCREEN) && ViewManager::getInstance()->getView(ViewTag::GAME_OVER_SCREEN)->isEnabled())
                this->stop();
        }
        // this->pTimeable->update();
    }
}

/*void Timer::switchView() {
    if(this->pSwitchable == NULL) {
        std::cout << "[ERROR] : One or more dependencies are missing." << std::endl;
    }
    else {
        this->pSwitchable->switchView();
    }
}*/

void Timer::reset()
{
    this->bIsCounting = true;
    this->fTicks = 120.0f;
    // this->fUpdateTicks = 0.0f;
}

void Timer::stop()
{
    this->bIsCounting = false;
}

void Timer::setTimeable(Timeable *pTimeable)
{
    this->pTimeable = pTimeable;
}

float components::Timer::getTime()
{
    return fTicks;
}
