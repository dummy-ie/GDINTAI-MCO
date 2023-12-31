#include "GameOverScreen.hpp"

using namespace views;

GameOverScreen::GameOverScreen(std::string strName) : View(ViewTag::GAME_OVER_SCREEN, strName) {
    ViewManager::getInstance()->registerView(this);
    this->setEnabled(false);
}

GameOverScreen::~GameOverScreen() {}

void GameOverScreen::initialize() {
    float fSpacing = 100;

    this->pGameOver = new Text(this->strName + " Game Over", "GAME OVER", FontManager::getInstance()->getFont(FontType::DEFAULT), 48);
    float fWidth = this->pGameOver->getText()->getLocalBounds().width;
    float fHeight = this->pGameOver->getText()->getLocalBounds().height;
    this->pGameOver->getText()->setPosition(SCREEN_WIDTH / 2 - fWidth / 2, SCREEN_HEIGHT / 2 - fHeight / 2);
    this->pGameOver->getText()->setOutlineThickness(5.f);
    this->pGameOver->getText()->setOutlineColor(sf::Color::White);
    this->attachChild(this->pGameOver);

    this->pContinue = new Text(this->strName + " Continue", "Continue", FontManager::getInstance()->getFont(FontType::DEFAULT), 24);
    this->attachChild(this->pContinue);
    fWidth = this->pContinue->getText()->getLocalBounds().width;
    this->pContinue->getText()->setPosition(SCREEN_WIDTH / 2 - fWidth / 2, this->pGameOver->getPosition().y + this->pContinue->getGlobalBounds().height + fSpacing);
    this->pContinue->getText()->setOutlineThickness(5.f);
    this->pContinue->getText()->setOutlineColor(sf::Color::White);
    sf::FloatRect CBounds = this->pContinue->getText()->getGlobalBounds();
    this->pButton = new Button(this->strName + " Continue Button", CBounds);
    this->attachChild(this->pButton);
    this->pButton->setListener(this);

    this->pGameStatus = new Text(this->strName + " Game Status", "DRAW", FontManager::getInstance()->getFont(FontType::DEFAULT), 24);
    this->attachChild(this->pGameStatus);
    fWidth = this->pGameStatus->getText()->getLocalBounds().width;
    this->pGameStatus->getText()->setPosition(SCREEN_WIDTH / 2 - fWidth / 2, this->pContinue->getPosition().y + this->pGameStatus->getGlobalBounds().height + fSpacing * 2.5);
    this->pGameStatus->getText()->setOutlineThickness(5.f);
    this->pGameStatus->getText()->setOutlineColor(sf::Color::White);
}

void GameOverScreen::setGameStatus(int nStatus)
{
    switch (nStatus)
    {
    case 0:
        this->pGameStatus->setText("You WIN");
        break;
    case 1:
        this->pGameStatus->setText("You LOSE");
        break;
    case 2:
        this->pGameStatus->setText("DRAW");
        break;
    
    default:
        this->pGameStatus->setText("L Bozo");
        break;
    }

    float fWidth = this->pGameStatus->getText()->getLocalBounds().width;
    float fSpacing = 100;
    this->pGameStatus->getText()->setPosition(SCREEN_WIDTH / 2 - fWidth / 2, this->pContinue->getPosition().y + this->pGameStatus->getGlobalBounds().height + fSpacing * 2.5);
}

void GameOverScreen::onClick(Button* pButton) {
    // buggy
    if (pButton->getName().find("Continue Button") != std::string::npos)
        this->pContinue->setColor(sf::Color::White);
}

void GameOverScreen::onHover(Button *pButton)
{
    if (pButton->getName().find("Continue Button") != std::string::npos)
        this->pContinue->setColor(sf::Color::Green);
    
}

void GameOverScreen::onRelease(Button* pButton) {
    if (pButton->getName().find("Continue Button") != std::string::npos) {
        std::cout << "[CONTINUE]" << std::endl;
        SceneManager::getInstance()->loadScene(SceneTag::GAME_MENU);
    }
}

void GameOverScreen::reset(Button* pButton) {
    if (pButton->getName().find("Continue Button") != std::string::npos) {
        this->pContinue->setColor(sf::Color::Black);
    }
}