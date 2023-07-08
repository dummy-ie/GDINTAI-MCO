#ifndef LISTENERS_BUTTON_LISTENER_HPP
#define LISTENERS_BUTTON_LISTENER_HPP

namespace views {
    class Button;
}

namespace listeners {
    using namespace views;
    
    class ButtonListener {
        public:
            virtual ~ButtonListener() {}

        public:
            virtual void onClick(Button* pButton) = 0;
            virtual void onHover(Button* pButton) = 0;
            virtual void onRelease(Button* pButton) = 0;
            virtual void reset(Button* pButton) = 0;
    };
}

#endif