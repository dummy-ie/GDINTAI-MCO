#include "TextureManager.hpp"

using namespace controllers;

void TextureManager::loadAll() {
    this->loadBackgroundFolder();
    this->loadTankFolder();
    this->loadWallFolder();
}

void TextureManager::loadBackgroundFolder() {
    sf::Texture* pTexture = NULL;

    pTexture = new sf::Texture();
    pTexture->loadFromFile("View/Image/menu_background.jpg");
    this->mapTexture[AssetType::MENU_BACKGROUND].push_back(pTexture);
}

void TextureManager::loadTankFolder() {
    sf::Texture* pTexture = NULL;

    AssetType EType = AssetType::PLAYER_TANK;
    pTexture = new sf::Texture();
    pTexture->loadFromFile("View/Image/texture.png", sf::IntRect(768, 128, 32, 32));
    this->mapTexture[EType].push_back(pTexture);

    pTexture = new sf::Texture();
    pTexture->loadFromFile("View/Image/texture.png", sf::IntRect(768, 160, 32, 32));
    this->mapTexture[EType].push_back(pTexture);

    pTexture = new sf::Texture();
    pTexture->loadFromFile("View/Image/enemy.png");
    this->mapTexture[AssetType::ENEMY_TANK].push_back(pTexture);

    pTexture = new sf::Texture();
    pTexture->loadFromFile("View/Image/texture.png", sf::IntRect(944, 128, 8, 8));
    this->mapTexture[AssetType::BULLET].push_back(pTexture);

    int nOffset = 31;
    for (int i = 0; i < 5; i++) {
        pTexture = new sf::Texture();
        pTexture->loadFromFile("View/Image/texture.png", sf::IntRect(1108, nOffset * i, 31, 31));
        this->mapTexture[AssetType::BULLET].push_back(pTexture);
    }
}

void TextureManager::loadWallFolder() {
    sf::Texture* pTexture = NULL;

    pTexture = new sf::Texture();
    pTexture->loadFromFile("View/Image/texture.png", sf::IntRect(928, 144, 16, 16));
    this->mapTexture[AssetType::STONE].push_back(pTexture);

    pTexture = new sf::Texture();
    pTexture->loadFromFile("View/Image/brick.png");
    this->mapTexture[AssetType::BRICK].push_back(pTexture);

    pTexture = new sf::Texture();
    pTexture->loadFromFile("View/Image/bush.png");
    this->mapTexture[AssetType::BUSH].push_back(pTexture);
}

std::vector<sf::Texture*> TextureManager::getTexture(AssetType EType) {
    return this->mapTexture[EType];
}

sf::Texture* TextureManager::getTextureAt(AssetType EType, int nFrame) {
    if(!this->mapTexture[EType].empty())
        return this->mapTexture[EType][nFrame];
        
    else {
        std::cout << "[ERROR] : No Texture found." << std::endl;
        return NULL;
    }
}

TextureManager* TextureManager::P_SHARED_INSTANCE = NULL;
TextureManager::TextureManager() {}
TextureManager::TextureManager(const TextureManager&) {}

TextureManager* TextureManager::getInstance() {
    if(P_SHARED_INSTANCE == NULL)
        P_SHARED_INSTANCE = new TextureManager();

    return P_SHARED_INSTANCE;
}