#ifndef VIEWS_IMAGE_HPP
#define VIEWS_IMAGE_HPP

#include "../Model/AnimatedTexture.hpp"
#include "../Model/GameObject.hpp"
#include "../Model/Component/Renderer/Renderer.hpp"

namespace views {
    using namespace components;
    using namespace models;

    class Image : public GameObject {
        public:
            Image(std::string strName, AnimatedTexture* pTexture);

        public:
            void initialize();
    };
}

#endif