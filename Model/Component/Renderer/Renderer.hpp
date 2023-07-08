#ifndef COMPONENTS_RENDERER_HPP
#define COMPONENTS_RENDERER_HPP

#include "../../Enum/EnumComponentType.hpp"

#include "../Component.hpp"

namespace components {
    class Renderer : public Component {
        private:
            sf::RenderWindow* pWindow;
            sf::Drawable* pDrawable;
            sf::RenderStates CRenderStates;

        public:
            Renderer(std::string strName);

        public:
            void perform();
            void flip();
            void assignTargetWindow(sf::RenderWindow* pWindow);
            void assignDrawable(sf::Drawable* pDrawable);
            void setRenderStates(sf::RenderStates CRenderStates);
    };
}

#endif