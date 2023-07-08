#ifndef MODELS_BACKGROUND_HPP
#define MODELS_BACKGROUND_HPP

#include "../GameObject.hpp"
#include "../AnimatedTexture.hpp"

#include "../Component/Renderer/Renderer.hpp"

namespace models {
    using namespace components;

    class Background : public GameObject {
        public:
            Background(std::string strName, AnimatedTexture* pTexture);
            ~Background();
            
        public:
            void initialize();
    };
}

#endif