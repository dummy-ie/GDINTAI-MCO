#include "ButtonInput.hpp"

using namespace components;

ButtonInput::ButtonInput(std::string strName, ButtonListener* pListener) : GeneralInput(strName) {
    this->pListener = pListener;
    this->bLeftClick = false;
}

void ButtonInput::perform() {
    switch(this->eEvent.type) {
        case sf::Event::MouseMoved:
            this->processMouseMove();
            break;

        case sf::Event::MouseButtonPressed:
            this->processMouseInput(true);
            break;
            
        case sf::Event::MouseButtonReleased:
            this->processMouseInput(false);
            break;
        
        default:
            break;
    }
}

void ButtonInput::processMouseInput(bool bPressed) {
    Button* pButton = (Button*)this->getOwner();
    sf::Mouse::Button inMouse = this->eEvent.mouseButton.button;
    sf::Vector2f vecLocation = sf::Vector2f(this->eEvent.mouseButton.x, this->eEvent.mouseButton.y);
          
    switch(inMouse) {
        case sf::Mouse::Left:
            this->bLeftClick = bPressed;
            if(this->bLeftClick && this->contains(pButton, vecLocation)) {
                pButton->changeState(ButtonState::PRESSED);
                this->pListener->onClick(pButton);
            }
            if(!this->bLeftClick && this->contains(pButton, vecLocation)) {
                pButton->changeState(ButtonState::NORMAL);
                this->pListener->onRelease(pButton);
                this->pListener->reset(pButton);
            }
            break;
        default:
            break;
    }
}

void ButtonInput::processMouseMove() {
    Button* pButton = (Button*)this->getOwner();
    sf::Vector2f vecLocation = sf::Vector2f(this->eEvent.mouseMove.x, this->eEvent.mouseMove.y);

    if (!this->bLeftClick && this->contains(pButton, vecLocation))
    {
        pButton->changeState(ButtonState::HOVER);
        this->pListener->onHover(pButton);
    }
    if (!this->bLeftClick && !this->contains(pButton, vecLocation)) {
        pButton->changeState(ButtonState::NORMAL);
        this->pListener->reset(pButton);
    }
}

bool ButtonInput::contains(Button* pButton, sf::Vector2f vecLocation) {
    if(pButton->getGlobalBounds().contains(vecLocation)) 
        return true;

    return false;   
}

