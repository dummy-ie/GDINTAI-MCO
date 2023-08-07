#ifndef INTERFACES_SPEEDABLE_HPP
#define INTERFACES_SPEEDABLE_HPP

namespace interfaces {
    using namespace models;
    class Speedable {
        public:
            ~Speedable() {}

        public:
            virtual void speed(float fBonusSpeed) = 0;
            virtual void unspeed() = 0;
    };
}

#endif