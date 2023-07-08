#ifndef VIEWS_BUTTON_HPP
#define VIEWS_BUTTON_HPP

#include "../Model/Enum/EnumButtonState.hpp"

#include "../Model/AnimatedTexture.hpp"
#include "../Model/GameObject.hpp"

#include "../Model/Component/Input/ButtonInput.hpp"
#include "../Model/Component/Renderer/Renderer.hpp"

#include "../View/Interface/ButtonListener.hpp"

namespace views {
    using namespace components;
    using namespace listeners;
    using namespace models;

    class Button : public GameObject {
        private:
            ButtonListener* pListener;
            sf::FloatRect CBounds;

        public:
            Button(std::string strName, AnimatedTexture* pTexture);
            Button(std::string strName, sf::FloatRect CBounds, AnimatedTexture* pTexture = NULL);
            ~Button();

        public:
            void initialize();
            void changeState(ButtonState EState);

        public:
            void setListener(ButtonListener* pListener);

        public:
            sf::FloatRect getGlobalBounds();
    };
}

#endif