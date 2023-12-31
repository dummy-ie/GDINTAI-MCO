#ifndef CONTROLLERS_VIEW_MANAGER_HPP
#define CONTROLLERS_VIEW_MANAGER_HPP

#include <unordered_map>

#include "../../Model/Enum/EnumViewTag.hpp"
#include "../../View/View.hpp"

namespace systems {
    using namespace views;
    class ViewManager {
		private:
            std::unordered_map<ViewTag, View*> mapView;

        public:
            void registerView(View* pView);
            void unregisterView(View* pView);
        
        public:
            View* getView(ViewTag ETag);
			
        private:
		    static ViewManager* P_SHARED_INSTANCE;

	    private:
		    ViewManager();
		    ViewManager(ViewManager const&);
		    ViewManager& operator = (ViewManager const&);

	    public:
		    static ViewManager* getInstance();
    };
}

#endif