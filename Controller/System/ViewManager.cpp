#include "ViewManager.hpp"

using namespace systems;

void ViewManager::registerView(View* pView) {
    this->mapView[pView->getTag()] = pView;
}

void ViewManager::unregisterView(View* pView) {
    this->mapView.erase(pView->getTag());
}

View* ViewManager::getView(ViewTag ETag) {
    return this->mapView[ETag];
}

ViewManager* ViewManager::P_SHARED_INSTANCE = NULL;
ViewManager::ViewManager() {}
ViewManager::ViewManager(const ViewManager&) {}

ViewManager* ViewManager::getInstance() {
    if(P_SHARED_INSTANCE == NULL)
        P_SHARED_INSTANCE = new ViewManager();

    return P_SHARED_INSTANCE;
}