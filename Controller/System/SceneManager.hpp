#ifndef SYSTEMS_SCENE_MANAGER_HPP
#define SYSTEMS_SCENE_MANAGER_HPP

#include "../../Model/Enum/EnumSceneTag.hpp"

#include "../../Model/Scene.hpp"

namespace systems {
    using namespace models;
    class SceneManager {
        private:
            std::unordered_map<SceneTag, Scene*> mapScene;
            Scene* pActiveScene;
            bool bLoading;
            SceneTag ESceneToLoad;

        public:
            void registerScene(Scene* pScene);
            void loadScene(SceneTag ETag);
            void unloadScene();
            void checkLoadScene();

        public:
            bool isLoaded(SceneTag ETag);

        /* * * * * * * * * * * * * * * * * * * * * 
         *       SINGLETON-RELATED CONTENT       * 
         * * * * * * * * * * * * * * * * * * * * */
        private:
            static SceneManager* P_SHARED_INSTANCE;

        private:
            SceneManager();
            SceneManager(const SceneManager&);
            SceneManager& operator = (const SceneManager&);

        public:
            static SceneManager* getInstance();
        /* * * * * * * * * * * * * * * * * * * * */
    };
}

#endif