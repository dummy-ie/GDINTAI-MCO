#include "AnimatedTexture.hpp"

using namespace models;

AnimatedTexture::AnimatedTexture(std::vector<sf::Texture*> vecFrames) {
    this->vecFrames = vecFrames;
    this->nCurrentFrame = 0;
}

void AnimatedTexture::incrementFrame() {
    this->setCurrentFrame(this->nCurrentFrame + 1);
}

sf::Texture* AnimatedTexture::getFrame() {
    return this->vecFrames[this->nCurrentFrame];
}

int AnimatedTexture::getFrameSize() {
    return this->vecFrames.size();
}

int AnimatedTexture::getCurrentFrame() {
    return this->nCurrentFrame;
}

void AnimatedTexture::setCurrentFrame(int nCurrentFrame) {
    if(nCurrentFrame < 0 || nCurrentFrame >= this->vecFrames.size()) {
        nCurrentFrame = 0;
        std::cout << "[WARNING] : nCurrentFrame out-of-bounds. Setting back to ZERO." << std::endl;
    }

    this->nCurrentFrame = nCurrentFrame;
}
