#include "GameMenu.hpp"

using namespace scenes;

GameMenu::GameMenu() : Scene(SceneTag::GAME_MENU) {}

GameMenu::~GameMenu() {}

void GameMenu::onLoadResources() {
    
}

void GameMenu::onLoadObjects() {
    this->createBackground();

    this->createUserInterface();
}

void GameMenu::onUnloadResources() {
    
}

void GameMenu::createBackground() {
    AssetType EType = AssetType::MENU_BACKGROUND;
    AnimatedTexture* pTexture = new AnimatedTexture(TextureManager::getInstance()->getTexture(EType));

    Background* pBackground = new Background("Menu Background", pTexture);
    this->registerObject(pBackground);
}

void GameMenu::createUserInterface() {
    TitleScreen* pTitleScreen = new TitleScreen("Title Screen");
    this->registerObject(pTitleScreen);
}