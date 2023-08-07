#include "TitleScreen.hpp"

using namespace views;

TitleScreen::TitleScreen(std::string strName) : View(ViewTag::TITLE_SCREEN, strName) {
    ViewManager::getInstance()->registerView(this);
}

TitleScreen::~TitleScreen() {}

void TitleScreen::initialize() {
    float fSpacing = 100;

    Text* pText = new Text(this->strName + " Title", "Tanky Tanks", FontManager::getInstance()->getFont(FontType::DEFAULT), 48);
    float fWidth = pText->getText()->getLocalBounds().width;
    pText->getText()->setPosition(SCREEN_WIDTH / 2 - fWidth / 2, 21);
    this->attachChild(pText);

    this->pStart = new Text(this->strName + " Start", "Start", FontManager::getInstance()->getFont(FontType::DEFAULT), 24);
    this->attachChild(this->pStart);
    fWidth = this->pStart->getText()->getLocalBounds().width;
    this->pStart->getText()->setPosition(SCREEN_WIDTH / 2 - fWidth / 2, fSpacing * 2);
    sf::FloatRect CBounds = this->pStart->getText()->getGlobalBounds();
    Button* pButton = new Button(this->strName + " Start Button", CBounds);
    this->attachChild(pButton);
    pButton->setListener(this);

    this->pLeaderboards = new Text(this->strName + " Leaderboards", "Leaderboards", FontManager::getInstance()->getFont(FontType::DEFAULT), 24);
    this->attachChild(this->pLeaderboards);
    fWidth = this->pLeaderboards->getText()->getLocalBounds().width;
    this->pLeaderboards->getText()->setPosition(SCREEN_WIDTH / 2 - fWidth / 2, fSpacing * 2.5);
    CBounds = this->pLeaderboards->getText()->getGlobalBounds();
    pButton = new Button(this->strName + " Leaderboards Button", CBounds);
    this->attachChild(pButton);
    pButton->setListener(this);

    this->pExit = new Text(this->strName + " Exit", "Exit", FontManager::getInstance()->getFont(FontType::DEFAULT), 24);
    this->attachChild(this->pExit);
    fWidth = this->pExit->getText()->getLocalBounds().width;
    this->pExit->getText()->setPosition(SCREEN_WIDTH / 2 - fWidth / 2, fSpacing * 3);
    CBounds = this->pExit->getText()->getGlobalBounds();
    pButton = new Button(this->strName + " Exit Button", CBounds);
    this->attachChild(pButton);
    pButton->setListener(this);
}

void TitleScreen::onClick(Button* pButton) {
    if (pButton->getName().find("Start Button") != std::string::npos)
        this->pStart->setColor(sf::Color::White);

    if (pButton->getName().find("Leaderboards Button") != std::string::npos)
        this->pLeaderboards->setColor(sf::Color::White);
    
    if (pButton->getName().find("Exit Button") != std::string::npos)
    {
        this->pExit->setColor(sf::Color::White);
    }
}

void TitleScreen::onHover(Button *pButton)
{
    if (pButton->getName().find("Start Button") != std::string::npos)
        this->pStart->setColor(sf::Color::Green);

    if (pButton->getName().find("Leaderboards Button") != std::string::npos)
        this->pLeaderboards->setColor(sf::Color::Green);

    if (pButton->getName().find("Exit Button") != std::string::npos)
        this->pExit->setColor(sf::Color::Green);
    
}

void TitleScreen::onRelease(Button* pButton) {
    if (pButton->getName().find("Start Button") != std::string::npos) {
        std::cout << "[MAP SELECT START]" << std::endl;
        // SceneManager::getInstance()->loadScene(SceneTag::GAME_SPACE);
        if (ViewManager::getInstance()->getView(ViewTag::MAP_SELECT_SCREEN))
            ViewManager::getInstance()->getView(ViewTag::MAP_SELECT_SCREEN)->setEnabled(true);
        else
            std::cout << "map select screen doesn't exist" << std::endl;
        
        this->setEnabled(false);
    }

    if (pButton->getName().find("Leaderboards Button") != std::string::npos) {
        std::cout << "[Leaderboards Button]" << std::endl;
        // SceneManager::getInstance()->loadScene(SceneTag::GAME_SPACE);
        if (ViewManager::getInstance()->getView(ViewTag::LEADERBOARD_SCREEN))
            ViewManager::getInstance()->getView(ViewTag::LEADERBOARD_SCREEN)->setEnabled(true);
        else
            std::cout << "leaderboards screen doesn't exist" << std::endl;
        
        this->setEnabled(false);
    }

    if (pButton->getName().find("Exit Button") != std::string::npos) {
        std::cout << "[GAME EXIT]" << std::endl;
        std::exit(0);
    }
}

void TitleScreen::reset(Button* pButton) {
    if (pButton->getName().find("Start Button") != std::string::npos) {
        this->pStart->setColor(sf::Color::Black);
    }

    if (pButton->getName().find("Leaderboards Button") != std::string::npos) {
        this->pLeaderboards->setColor(sf::Color::Black);
    }

    if (pButton->getName().find("Exit Button") != std::string::npos) {
        this->pExit->setColor(sf::Color::Black);
    }
}