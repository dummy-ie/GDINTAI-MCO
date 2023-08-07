#ifndef VIEWS_TIMER_VIEW_HPP
#define VIEWS_TIMER_VIEW_HPP

#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

#include "../../Model/Component/Script/Interface/Timeable.hpp"
#include "../../Model/Component/Script/Timer.hpp"

#include "../View.hpp"
#include "../Text.hpp"
#include "../Button.hpp"

#include "../../Model/Enum/EnumFontType.hpp"
#include "../../Model/Enum/EnumViewTag.hpp"

#include "../../Controller/Singleton/FontManager.hpp"
#include "../../Controller/System/ViewManager.hpp"
#include "../../Controller/System/SceneManager.hpp"

namespace views
{
    using namespace systems;
    class TimerView : public View, public Timeable
    {
    private:
        Timer *pTimer;
        std::vector<Text *> vecTime;

    public:
        TimerView(std::string strName);
        ~TimerView() = default;

        void initialize();

        void createTimer();
        Text *copyText(Text *pReference, std::string strText, float fScale);
        void setTime(float fSeconds);
    };
} // namespace views

#endif // !VIEWS_TIMER_VIEW_HPP