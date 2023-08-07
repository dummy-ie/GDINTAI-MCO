#include "TimerView.hpp"

using namespace views;

TimerView::TimerView(std::string strName) : View(ViewTag::TIMER_VIEW, strName) {
    ViewManager::getInstance()->registerView(this);
    this->vecTime = {};

}

void TimerView::initialize()
{
    this->createTimer();
}

void TimerView::createTimer()
{
    pTimer = new Timer(this->strName + " Timer");
    this->attachComponent(pTimer);
    pTimer->setTimeable(this);
    pTimer->reset();

    float fScale = 24.f;
    Text *pColon = new Text(this->strName + " Time",
                            ":",
                            FontManager::getInstance()->getFont(FontType::DEFAULT),
                            fScale);

    sf::Color CColor = sf::Color::White;
    CColor.a = 127;
    pColon->getText()->setStyle(sf::Text::Bold);
    pColon->getText()->setOutlineThickness(3.0f);
    pColon->getText()->setOutlineColor(CColor);
    this->attachChild(pColon);

    CColor = sf::Color::Black;
    pColon->getText()->setFillColor(CColor);

    float fX = SCREEN_WIDTH / 2.f;
    float fY = SCREEN_HEIGHT - 100.f;
    pColon->setPosition({fX, fY});

    fX = pColon->getGlobalBounds().left - pColon->getGlobalBounds().width;
    fY = pColon->getGlobalBounds().top;
    float fPadding = fScale - (fScale * 0.3f);

    Text *pText = this->copyText(pColon, "0", fScale);
    this->vecTime.push_back(pText);
    fX = fX - ((pColon->getText()->getGlobalBounds().width + fPadding) * 2.f);
    fY -= (fScale * 0.3f);
    pText->setPosition({fX, fY});

    pText = this->copyText(pColon, "0", fScale);
    this->vecTime.push_back(pText);
    fX = this->vecTime[0]->getPosition().x;
    fX = fX + (pColon->getText()->getGlobalBounds().width + fPadding);
    pText->setPosition({fX, fY});

    pText = this->copyText(pColon, "0", fScale);
    this->vecTime.push_back(pText);
    fX = pColon->getPosition().x;
    fX = fX + (pColon->getText()->getGlobalBounds().width + fPadding) - (fScale * 0.2f);
    pText->setPosition({fX, fY});

    pText = this->copyText(pColon, "0", fScale);
    this->vecTime.push_back(pText);
    fX = this->vecTime[2]->getPosition().x;
    fX = fX + (pColon->getText()->getGlobalBounds().width + fPadding);
    pText->setPosition({fX, fY});

    this->setTime(120.f);
}

Text *TimerView::copyText(Text *pReference, std::string strText, float fScale)
{
    Text *pText = new Text(this->strName + " Text",
                           strText,
                           FontManager::getInstance()->getFont(FontType::DEFAULT),
                           fScale);

    this->attachChild(pText);

    pText->getText()->setStyle(pReference->getText()->getStyle());
    pText->getText()->setOutlineThickness(pReference->getText()->getOutlineThickness());
    pText->getText()->setOutlineColor(pReference->getText()->getOutlineColor());
    pText->getText()->setFillColor(pReference->getText()->getFillColor());

    pText->setPosition(pReference->getPosition());

    return pText;
}

void TimerView::setTime(float fSeconds)
{
    int ms = (int)(fSeconds * 1000.f);

    int h = ms / (1000 * 60 * 60);
    ms -= h * (1000 * 60 * 60);

    int m = ms / (1000 * 60);
    ms -= m * (1000 * 60);

    int s = ms / 1000;
    ms -= s * 1000;

    std::stringstream CStream;
    CStream << std::setfill('0') << std::setw(2) << m << std::setw(2) << s;
    // std::cout << std::setfill('0') << std::setw(2) << m << " : "<< std::setw(2) << s << std::endl;

    std::string strTime = CStream.str();
    // std::cout << "m: " << strTime.at() << std::endl;
    // std::cout << "s: " << s << std::endl;

    // if (strTime.length() < 5)
    //     strTime = "0" + strTime;

    // strTime.erase(2, 1);

    for (int i = 0; i < strTime.length(); i++)
    {
        this->vecTime.at(i)->setText(std::string(1, strTime.at(i)));
    }
}
