#ifndef MODELS_ANIMATED_TEXTURE_H
#define MODELS_ANIMATED_TEXTURE_H

#include "iostream"

namespace models {
    class AnimatedTexture {
        private:
            std::vector<sf::Texture*> vecFrames;
            int nCurrentFrame;
        
        public:
            AnimatedTexture(std::vector<sf::Texture*> vecFrames = {});

        public:
            void incrementFrame();

        public:
            sf::Texture* getFrame();
            int getFrameSize();
            int getCurrentFrame();
            void setCurrentFrame(int nCurrentFrame);
    };
}

#endif