#include "Image.hpp"

using namespace views;

Image::Image(std::string strName, AnimatedTexture* pTexture) : GameObject(strName, pTexture) {}

void Image::initialize() {
    this->setFrame(0);
    this->centerSpriteOrigin();

    Renderer* pRendererComponent = new Renderer(this->strName + " Image");
    pRendererComponent->assignDrawable(this->pSprite);

    this->attachComponent(pRendererComponent);
}
