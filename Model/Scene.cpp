#include "Scene.hpp"

using namespace models;

Scene::Scene(SceneTag ETag) {
    this->ETag = ETag;
}

Scene::~Scene() {}

void Scene::onUnloadObjects() {
    GameObjectManager::getInstance()->deleteAllObjects();
}

void Scene::registerObject(GameObject* pGameObject) {
    GameObjectManager::getInstance()->addObject(pGameObject);
    
}

SceneTag Scene::getTag() {
    return this->ETag;
}