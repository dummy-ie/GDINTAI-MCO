#ifndef INTERFACES_DAMAGEABLE_HPP
#define INTERFACES_DAMAGEABLE_HPP

namespace interfaces {
    using namespace models;
    class Damageable {
        public:
            ~Damageable() {}

        public:
            virtual void damage() = 0;
    };
}

#endif