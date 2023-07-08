#ifndef MODELS_POOLABLE_OBJECT_HPP
#define MODELS_POOLABLE_OBJECT_HPP

#include "../GameObject.hpp"
#include "../Enum/EnumPoolTag.hpp"

namespace models {
    class PoolableObject : public GameObject {
        protected:
            PoolTag ETag;

        public:
            PoolableObject(PoolTag ETag, std::string strName, AnimatedTexture* pTexture = NULL); 
            ~PoolableObject();

        public:
            virtual void initialize()       = 0;
            virtual void onActivate()       = 0;
            virtual void onRelease()        = 0;
            virtual PoolableObject* clone() = 0;

        public:
            PoolTag getTag();
    };
}

#endif