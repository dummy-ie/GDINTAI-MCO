#ifndef INTERFACES_TIMEABLE_HPP
#define INTERFACES_TIMEABLE_HPP

namespace interfaces {
    class Timeable {
        public:
            virtual ~Timeable() {}

        public:
            // virtual void proceed() = 0;
            // virtual void update() = 0;
            virtual void setTime(float fSeconds) = 0;
    };
}

#endif