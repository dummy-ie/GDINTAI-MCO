#include "TankInput.hpp"

using namespace components;

TankInput::TankInput(std::string strName) : GeneralInput(strName) {
    this->bSpace = false;
    this->bUp = false;
    this->bDown = false;
    this->bLeft = false;
    this->bRight = false;
}

void TankInput::perform() {
    switch(this->eEvent.type) {
        case sf::Event::KeyPressed:
            this->processKeyInput(true);
            break;
            
        case sf::Event::KeyReleased:
            this->processKeyInput(false);
            break;

        default:
            break;
    }
}

void TankInput::processKeyInput(bool bPressed) {
    sf::Keyboard::Key inKey = this->eEvent.key.code;

    switch(inKey) {
        case sf::Keyboard::Space:
            this->bSpace = bPressed;
            break;

        case sf::Keyboard::W:
            this->bUp = bPressed;
            this->bDown = false;
            this->bLeft = false;
            this->bRight = false;
            break;

        case sf::Keyboard::S:
            this->bUp = false;
            this->bDown = bPressed;
            this->bLeft = false;
            this->bRight = false;
            break;

        case sf::Keyboard::A:
            this->bUp = false;
            this->bDown = false;
            this->bLeft = bPressed;
            this->bRight = false;
            break;

        case sf::Keyboard::D:
            this->bUp = false;
            this->bDown = false;
            this->bLeft = false;
            this->bRight = bPressed;
            break;

        default:
            break;
    }
}

void TankInput::resetSpace() {
    this->bSpace = false;
}

bool TankInput::isSpace() {
    return this->bSpace;
}

bool TankInput::isUp() {
    return this->bUp;
}

bool TankInput::isDown() {
    return this->bDown;
}

bool TankInput::isLeft() {
    return this->bLeft;
}

bool TankInput::isRight() {
    return this->bRight;
}
