#ifndef COMPONENTS_BUTTON_INPUT_HPP
#define COMPONENTS_BUTTON_INPUT_HPP

#include "GeneralInput.hpp"

#include "../../Enum/EnumButtonState.hpp"
#include "../../../View/Interface/ButtonListener.hpp"
#include "../../../View/Button.hpp"

namespace components {
    using namespace listeners;
    
    class ButtonInput : public GeneralInput {
        private:
            bool bLeftClick;
            ButtonListener* pListener;

        public:
            ButtonInput(std::string strName, ButtonListener* pListener);

        public:
            void perform();

        private:
            void processMouseInput(bool bPressed);
            void processMouseMove();
            bool contains(Button* pButton, sf::Vector2f vecLocation);
    };
}

#endif