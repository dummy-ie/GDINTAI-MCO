#ifndef MODELS_GAME_OBJECT_HPP
#define MODELS_GAME_OBJECT_HPP

#include "iostream"

#include "Enum/EnumComponentType.hpp"

#include "AnimatedTexture.hpp"
#include "Component/Component.hpp"
#include "Component/Input/GeneralInput.hpp"

#include "Component/Renderer/Renderer.hpp"

namespace models {
    using namespace components;
    
    class GameObject {
        protected:
            bool bEnabled;
            std::string strName;
            sf::Sprite* pSprite;
            AnimatedTexture* pTexture;

            GameObject* pParent;
            std::vector<GameObject*> vecChildren;
            std::vector<Component*> vecComponent;

        public:
            GameObject(std::string strName, AnimatedTexture* pTexture = NULL);
            virtual ~GameObject() = default;

        public:
            virtual void initialize() = 0;
            virtual void processInput(sf::Event eEvent);
            virtual void update(sf::Time tDeltaTime);
            virtual void draw(sf::RenderWindow* pWindow, sf::RenderStates CRenderStates);

        public:
            void attachChild(GameObject* pChild);
            void detachChild(GameObject* pChild);

            void attachComponent(Component* pComponent);
            void detachComponent(Component* pComponent);
            Component* findComponentByName(std::string strName);
            std::vector<Component*> getComponents(ComponentType EType);
            std::vector<Component*> getComponentsRecursively(ComponentType EType, bool bInclusive = true);

            void incrementFrame();
            void centerSpriteOrigin();

        public:
            virtual void setFrame(int nFrame);

        public:
            bool isEnabled();
            void setEnabled(bool bEnabled);

            std::string getName();
            sf::Sprite* getSprite();
            virtual sf::FloatRect getGlobalBounds();

            GameObject* getParent();
            void setParent(GameObject* pParent);

            int getFrameSize();
            int getCurrentFrame();
    };
}

#endif