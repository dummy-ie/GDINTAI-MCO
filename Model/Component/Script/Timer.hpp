#ifndef COMPONENTS_TIMER_HPP
#define COMPONENTS_TIMER_HPP

#include "../../Enum/EnumComponentType.hpp"

#include "../Component.hpp"

#include "Interface/Timeable.hpp"

namespace components {
    using namespace models;
    using namespace systems;
    class Timer : public Component {
        private:
            Timeable* pTimeable;

            bool bIsCounting = true;

            float fTicks;
            float fUpdateTicks;
            float fUpdateInterval;
        
        public:
            Timer(std::string strName);

        public:
            void perform();
            void reset();
            void stop();

        private:

        public:
            void setTimeable(Timeable* pTimeable);
            float getTime();
    };
}

#endif