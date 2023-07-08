#include "Renderer.hpp"

using namespace components;

Renderer::Renderer(std::string strName) : Component(strName, ComponentType::RENDERER) {
    this->CRenderStates = sf::RenderStates::Default;
}

void Renderer::perform() {
    this->pWindow->draw(*this->pDrawable, this->CRenderStates);
}
void Renderer::flip() {
    sf::Sprite* pSprite = (sf::Sprite*)this->pDrawable;
    pSprite->setScale(-pSprite->getScale().x, pSprite->getScale().y);
}

void Renderer::assignTargetWindow(sf::RenderWindow* pWindow) {
    this->pWindow = pWindow;
}

void Renderer::assignDrawable(sf::Drawable* pDrawable) {
    this->pDrawable = pDrawable;
}

void Renderer::setRenderStates(sf::RenderStates CRenderStates) {
    this->CRenderStates = CRenderStates;
}