#ifndef COMPONENTS_TANK_INPUT_HPP
#define COMPONENTS_TANK_INPUT_HPP

#include "GeneralInput.hpp"

namespace components {
    class TankInput : public GeneralInput {
        private:
            bool bSpace;
            bool bUp;
            bool bDown;
            bool bLeft;
            bool bRight;
            
        public:
            TankInput(std::string strName);

        public:
            void perform();
            void resetSpace();
            void resetMovement();

        private:
            void processKeyInput(bool bPressed);

        public:
            bool isSpace();
    };
}

#endif