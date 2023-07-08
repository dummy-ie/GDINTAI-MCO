#include "FontManager.hpp"

using namespace controllers;

void FontManager::loadAll() {
    this->create(FontType::DEFAULT, "Orbitron");
}

sf::Font* FontManager::getFont(FontType EType) {
    return this->mapFont[EType];
}

void FontManager::create(FontType EType, std::string strName) {
    sf::Font* pFont = new sf::Font();
    std::string strPath = "View/Font/" + strName + "/" + strName + "-Regular.ttf";
    
    std::cout << "[FONT] : " << strPath << std::endl;

    pFont->loadFromFile(strPath);
    this->mapFont[EType] = pFont;
}

/* * * * * * * * * * * * * * * * * * * * * 
 *       SINGLETON-RELATED CONTENT       * 
 * * * * * * * * * * * * * * * * * * * * */
FontManager* FontManager::P_SHARED_INSTANCE = NULL;
FontManager::FontManager() {}
FontManager::FontManager(const FontManager&) {}

FontManager* FontManager::getInstance() {
    if(P_SHARED_INSTANCE == NULL)
        P_SHARED_INSTANCE = new FontManager();

    return P_SHARED_INSTANCE;
}
/* * * * * * * * * * * * * * * * * * * * */
