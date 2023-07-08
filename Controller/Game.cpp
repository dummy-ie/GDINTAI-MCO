#include "Game.hpp"

using namespace controllers;

Game::Game() : rwWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Risk of Death", sf::Style::Titlebar | sf::Style::Close) {
    this->rwWindow.setFramerateLimit(FRAME_RATE_LIMIT);

    TextureManager::getInstance()->loadAll();
    //SFXManager::getInstance()->loadAll();
    FontManager::getInstance()->loadAll();

    SceneManager::getInstance()->registerScene(new GameMenu());
    SceneManager::getInstance()->registerScene(new GameSpace());

    SceneManager::getInstance()->loadScene(SceneTag::GAME_MENU);
}

void Game::run() {
    sf::Clock CClock = sf::Clock();
    sf::Time tLastUpdate = sf::Time::Zero;
    sf::Time tTimePerFrame = sf::seconds(1.0f / FRAME_RATE_LIMIT);
    while(this->rwWindow.isOpen()) {
        this->processEvents();
        tLastUpdate += CClock.restart();
        while(tLastUpdate > tTimePerFrame) {
            tLastUpdate -= tTimePerFrame;
            this->update(tTimePerFrame);
        }
        SceneManager::getInstance()->checkLoadScene();
        this->render();
    }
}

void Game::processEvents() {
    sf::Event eEvent;

    while(this->rwWindow.pollEvent(eEvent)) {
        switch(eEvent.type) {
            case sf::Event::Closed:
                this->rwWindow.close();
                break;
  
            default:
                GameObjectManager::getInstance()->processInput(eEvent);
                break;
        }
    }
}

void Game::update(sf::Time tDeltaTime) {
    GameObjectManager::getInstance()->update(tDeltaTime);
}

void Game::render() {
    this->rwWindow.clear();
    GameObjectManager::getInstance()->draw(&this->rwWindow);
    this->rwWindow.display();
}