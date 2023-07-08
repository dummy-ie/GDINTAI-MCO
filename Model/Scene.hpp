#ifndef MODELS_SCENE_HPP
#define MODELS_SCENE_HPP

#include "../Controller/Singleton/GameObjectManager.hpp"

#include "Enum/EnumSceneTag.hpp"

#include "GameObject.hpp"

namespace models {
    using namespace controllers;
    class Scene {
        private:
            SceneTag ETag;

        public:
            Scene(SceneTag ETag);
            ~Scene();

        public:
            virtual void onLoadResources() = 0;
            virtual void onLoadObjects() = 0;
            virtual void onUnloadResources() = 0;
            virtual void onUnloadObjects();

        protected:
            void registerObject(GameObject* pGameObject);

        public:
            SceneTag getTag();
    };
}

#endif