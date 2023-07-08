#ifndef CONTROLLERS_GAME_OBJECT_POOL_HPP
#define CONTROLLERS_GAME_OBJECT_POOL_HPP

#include "iostream"
#include "../../Model/Enum/EnumPoolTag.hpp"
#include "../../Model/GameObject.hpp"
#include "../../Model/Pooling/PoolableObject.hpp"

namespace controllers {
    class GameObjectPool {
        private:
            PoolTag ETag;
            int nPoolSize;
            PoolableObject* pPoolableReference;
            GameObject* pParent;

            std::vector<PoolableObject*> vecAvailableObject;
            std::vector<PoolableObject*> vecUsedObject;

        public:
            GameObjectPool(PoolTag ETag, int nPoolSize, PoolableObject* pPoolableReference, GameObject* pParent = NULL);
            ~GameObjectPool();
        
        public:
            void initialize();

            PoolableObject* requestPoolable();
            std::vector<PoolableObject*> requestPoolableBatch(int nRequestSize);
            void releasePoolable(PoolableObject* pPoolableObject);
            void releasePoolableBatch(std::vector<PoolableObject*> vecPoolableObject);

        private:
            bool hasAvailable(int nRequestSize);
            void setEnabled(PoolableObject* pPoolableObject, bool bEnabled);

        public:
            PoolTag getTag();
    };
}

#endif