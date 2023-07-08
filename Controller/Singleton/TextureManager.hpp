#ifndef CONTROLLERS_TEXTURE_MANAGER_HPP
#define CONTROLLERS_TEXTURE_MANAGER_HPP

#include "../../Model/Enum/EnumAssetType.hpp"
namespace controllers {
    class TextureManager {
        private:
            std::unordered_map<AssetType, std::vector<sf::Texture*>> mapTexture;

        public:
            void loadAll();
            std::vector<sf::Texture*> getTexture(AssetType EType);
            sf::Texture* getTextureAt(AssetType EType, int nFrame);

		private:
			void loadBackgroundFolder();
            void loadTankFolder();

        private:
		    static TextureManager* P_SHARED_INSTANCE;

	    private:
		    TextureManager();
		    TextureManager(TextureManager const&);
		    TextureManager& operator = (TextureManager const&);

	    public:
		    static TextureManager* getInstance();
    };
}

#endif