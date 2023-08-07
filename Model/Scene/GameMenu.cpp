#include "GameMenu.hpp"

using namespace scenes;

GameMenu::GameMenu() : Scene(SceneTag::GAME_MENU) {}

GameMenu::~GameMenu() {}

void GameMenu::onLoadResources() {
    
}

void GameMenu::onLoadObjects() {
    this->createBackground();
    this->createMenuInterface();
    this->createMapSelectionInterface();
    this->createLeaderboardInterface();
}

void GameMenu::onUnloadResources() {
    
}

void GameMenu::createBackground() {
    AssetType EType = AssetType::MENU_BACKGROUND;
    AnimatedTexture* pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));

    Background* pBackground = new Background("Menu Background", pTexture);
    this->registerObject(pBackground);
}

void GameMenu::createMenuInterface() {
    TitleScreen* pTitleScreen = new TitleScreen("Title Screen");
    this->registerObject(pTitleScreen);
}

void GameMenu::createMapSelectionInterface()
{
    MapSelectionScreen* pMapSelectionScreen = new MapSelectionScreen("Map Selection Screen");
    this->registerObject(pMapSelectionScreen);
}

void GameMenu::createLeaderboardInterface()
{
    LeaderboardScreen* pLeaderboardScreen = new LeaderboardScreen("Leaderboard Screen");
    this->registerObject(pLeaderboardScreen);
}
