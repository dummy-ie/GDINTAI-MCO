#include "MapSelectionScreen.hpp"

using namespace views;

MapSelectionScreen::MapSelectionScreen(std::string strName) : View(ViewTag::MAP_SELECT_SCREEN, strName) {
    ViewManager::getInstance()->registerView(this);
    this->setEnabled(false);
}

MapSelectionScreen::~MapSelectionScreen() {}

void MapSelectionScreen::initialize() {
    float fSpacing = 100;

    Text* pText = new Text(this->strName + " Title", "Select Map", FontManager::getInstance()->getFont(FontType::DEFAULT), 48);
    float fWidth = pText->getText()->getLocalBounds().width;
    pText->getText()->setPosition(SCREEN_WIDTH / 2 - fWidth / 2, 21);
    this->attachChild(pText);

    this->pStart = new Text(this->strName + " Start", "Start", FontManager::getInstance()->getFont(FontType::DEFAULT), 24);
    this->attachChild(this->pStart);
    fWidth = this->pStart->getText()->getLocalBounds().width;
    this->pStart->getText()->setPosition(SCREEN_WIDTH / 2 - fWidth / 2, fSpacing);
    sf::FloatRect CBounds = this->pStart->getText()->getGlobalBounds();
    Button* pButton = new Button(this->strName + " Start Button", CBounds);
    this->attachChild(pButton);
    pButton->setListener(this);

    this->pReturn = new Text(this->strName + " Return", "Return", FontManager::getInstance()->getFont(FontType::DEFAULT), 24);
    this->attachChild(this->pReturn);
    fWidth = this->pReturn->getText()->getLocalBounds().width;
    this->pReturn->getText()->setPosition(SCREEN_WIDTH / 2 - fWidth / 2, fSpacing * 3);
    CBounds = this->pReturn->getText()->getGlobalBounds();
    pButton = new Button(this->strName + " Return Button", CBounds);
    this->attachChild(pButton);
    pButton->setListener(this);

    this->pMapSelect = new Text(this->strName + " Map Select", "Choose Map: " + std::to_string(this->nMapSelection),FontManager::getInstance()->getFont(FontType::DEFAULT), 24);
    this->attachChild(this->pMapSelect);
    fWidth = this->pMapSelect->getText()->getLocalBounds().width;
    this->pMapSelect->getText()->setPosition(SCREEN_WIDTH / 2 - fWidth / 2, fSpacing * 2);
    CBounds = this->pMapSelect->getText()->getGlobalBounds();
    pButton = new Button(this->strName + " Map Select Button", CBounds);
    this->attachChild(pButton);
    pButton->setListener(this);
}

void MapSelectionScreen::onClick(Button* pButton) {
    if (pButton->getName().find("Start Button") != std::string::npos)
        this->pStart->setColor(sf::Color::White);
    
    if (pButton->getName().find("Map Select Button") != std::string::npos)
        this->pMapSelect->setColor(sf::Color::White);
    
    if (pButton->getName().find("Return Button") != std::string::npos)
    {
        this->pReturn->setColor(sf::Color::White);
    }
}

void MapSelectionScreen::onHover(Button *pButton)
{
    if (pButton->getName().find("Start Button") != std::string::npos)
        this->pStart->setColor(sf::Color::Green);

    if (pButton->getName().find("Map Select Button") != std::string::npos)
        this->pMapSelect->setColor(sf::Color::Green);

    if (pButton->getName().find("Return Button") != std::string::npos)
        this->pReturn->setColor(sf::Color::Green);
    
}

void MapSelectionScreen::onRelease(Button* pButton) {
    if (pButton->getName().find("Start Button") != std::string::npos) {
        std::cout << "[GAME START]" << std::endl;
        switch (nMapSelection)
        {
        case 1:
            MapManager::getInstance()->setMap(MAP_STAGE_1);
            break;
        case 2:
            MapManager::getInstance()->setMap(MAP_STAGE_2);
            break;
        case 3:
            MapManager::getInstance()->setMap(MAP_STAGE_3);
            break;
        
        default:
            MapManager::getInstance()->setMap(MAP_STAGE_1);
            std::cout << "Invalid map selection! Defaulting to 1..." << std::endl;
            break;
        }
        SceneManager::getInstance()->loadScene(SceneTag::GAME_SPACE);
    }

    if (pButton->getName().find("Map Select Button") != std::string::npos)
    {   
        this->nMapSelection++;
        if (this->nMapSelection > 3)
            this->nMapSelection = 1;

        this->pMapSelect->setText("Choose Map: " + std::to_string(this->nMapSelection));
    }

    if (pButton->getName().find("Return Button") != std::string::npos) {
        std::cout << "[MAP SELECT RETURN]" << std::endl;
        if (ViewManager::getInstance()->getView(ViewTag::TITLE_SCREEN))
            ViewManager::getInstance()->getView(ViewTag::TITLE_SCREEN)->setEnabled(true);
        else
            std::cout << "titel screen doesn't exist" << std::endl;
        
        this->setEnabled(false);
    }
}

void MapSelectionScreen::reset(Button* pButton) {
    if (pButton->getName().find("Start Button") != std::string::npos) {
        this->pStart->setColor(sf::Color::Black);
    }

    if (pButton->getName().find("Map Select Button") != std::string::npos)
        this->pMapSelect->setColor(sf::Color::Black);

    if (pButton->getName().find("Return Button") != std::string::npos) {
        this->pReturn->setColor(sf::Color::Black);
    }
}