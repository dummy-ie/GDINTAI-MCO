#include "Button.hpp"

using namespace views;

Button::Button(std::string strName, AnimatedTexture* pTexture) : GameObject(strName, pTexture) {}

Button::Button(std::string strName, sf::FloatRect CBounds, AnimatedTexture* pTexture) : GameObject(strName, pTexture) {
    this->CBounds = CBounds;
}

Button::~Button() {}

void Button::initialize() {
    //this->centerSpriteOrigin();

    if (this->pTexture != NULL) {
        this->setFrame(0);
        Renderer* pRendererComponent = new Renderer(this->strName + " Button");
        pRendererComponent->assignDrawable(this->pSprite);
        this->CBounds = this->pSprite->getGlobalBounds();
        this->attachComponent(pRendererComponent);
    }
}

void Button::changeState(ButtonState EState) {
    if (this->pTexture != NULL) {
        this->pTexture->setCurrentFrame((int)EState);
        this->setFrame(this->pTexture->getCurrentFrame());
    }
}

void Button::setListener(ButtonListener* pListener) {
    this->pListener = pListener;
    
    ButtonInput* pInputComponent = new ButtonInput(this->strName + " Input", this->pListener);
    this->attachComponent(pInputComponent);
}

sf::FloatRect Button::getGlobalBounds() {
    return this->CBounds;
}