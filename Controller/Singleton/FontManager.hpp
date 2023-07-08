#ifndef CONTROLLERS_FONT_MANAGER_HPP
#define CONTROLLERS_FONT_MANAGER_HPP

#include "../../Model/Enum/EnumFontType.hpp"

namespace controllers {
    class FontManager {
        private:
            std::unordered_map<FontType, sf::Font*> mapFont;

        public:
            void loadAll();
            sf::Font* getFont(FontType EType);

        private:
            void create(FontType EType, std::string strName);

        /* * * * * * * * * * * * * * * * * * * * * 
         *       SINGLETON-RELATED CONTENT       * 
         * * * * * * * * * * * * * * * * * * * * */
        private:
            static FontManager* P_SHARED_INSTANCE;

        private:
            FontManager();
            FontManager(const FontManager&);
            FontManager& operator = (const FontManager&);

        public:
            static FontManager* getInstance();
        /* * * * * * * * * * * * * * * * * * * * */
    };
}

#endif