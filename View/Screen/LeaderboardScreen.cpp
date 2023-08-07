#include "LeaderboardScreen.hpp"

using namespace views;

LeaderboardScreen::LeaderboardScreen(std::string strName) : View(ViewTag::LEADERBOARD_SCREEN, strName)
{
    this->vecScores = {};
    ViewManager::getInstance()->registerView(this);
    this->setEnabled(false);
}

LeaderboardScreen::~LeaderboardScreen() {}

void LeaderboardScreen::initialize()
{
    float fSpacing = 100;

    this->pReturn = new Text(this->strName + " Return", "Return", FontManager::getInstance()->getFont(FontType::DEFAULT), 24);
    this->attachChild(this->pReturn);
    float fWidth = this->pReturn->getText()->getLocalBounds().width;
    this->pReturn->getText()->setPosition(SCREEN_WIDTH / 2 - fWidth / 2, fSpacing * 3);
    sf::FloatRect CBounds = this->pReturn->getText()->getGlobalBounds();
    Button *pButton = new Button(this->strName + " Return Button", CBounds);
    this->attachChild(pButton);
    pButton->setListener(this);

    Text *pText = new Text(this->strName + " Title", "Leaderboard", FontManager::getInstance()->getFont(FontType::DEFAULT), 48);
    fWidth = pText->getText()->getLocalBounds().width;
    pText->getText()->setPosition(SCREEN_WIDTH / 2 - fWidth / 2, 21);
    this->attachChild(pText);

    //     this->vecTopTimes.push_back(new GameTimer("Leaderboard Top Score " + std::to_string(i)));

    for (size_t i = 0; i < 5; i++)
    {
        // std::vector<Text *> vecTemp;
        float fScale = 24.f;
        Text *pScore = new Text(this->strName + " Score",
                                "0000",
                                FontManager::getInstance()->getFont(FontType::DEFAULT),
                                fScale);

        sf::Color CColor = sf::Color::White;
        pScore->getText()->setStyle(sf::Text::Bold);
        // pScore->getText()->setOutlineThickness(3.0f);
        // pScore->getText()->setOutlineColor(CColor);
        this->attachChild(pScore);

        CColor = sf::Color::Black;
        // CColor.a = 150;
        pScore->getText()->setFillColor(CColor);

        float fX = SCREEN_WIDTH / 2.f - pScore->getText()->getGlobalBounds().width / 2.f;
        float fY = (pText->getText()->getPosition().y + 30.f) + pScore->getText()->getGlobalBounds().height + 30.f * (i + 1);
        pScore->setPosition({fX, fY});

        this->vecScores.push_back(pScore);

        // fX = pColon->getGlobalBounds().left - pColon->getGlobalBounds().width;
        // fY = pColon->getGlobalBounds().top;
        // float fPadding = fScale - (fScale * 0.3f);

        // Text *pText = this->copyText(pColon, "0", fScale);
        // vecTemp.push_back(pText);
        // fX = fX - ((pColon->getText()->getGlobalBounds().width + fPadding) * 2.f);
        // fY -= (fScale * 0.3f);
        // pText->setPosition({fX, fY});

        // pText = this->copyText(pColon, "0", fScale);
        // vecTemp.push_back(pText);
        // fX = vecTemp[0]->getPosition().x;
        // fX = fX + (pColon->getText()->getGlobalBounds().width + fPadding);
        // pText->setPosition({fX, fY});

        // pText = this->copyText(pColon, "0", fScale);
        // vecTemp.push_back(pText);
        // fX = pColon->getPosition().x;
        // fX = fX + (pColon->getText()->getGlobalBounds().width + fPadding) - (fScale * 0.2f);
        // pText->setPosition({fX, fY});

        // pText = this->copyText(pColon, "0", fScale);
        // vecTemp.push_back(pText);
        // fX = vecTemp[2]->getPosition().x;
        // fX = fX + (pColon->getText()->getGlobalBounds().width + fPadding);
        // pText->setPosition({fX, fY});

        // this->vecScores.push_back(vecTemp);
    }

    loadScores();

    // for (size_t i = 0; i < this->vecScores.size(); i++)
    // {
    // fWidth = getLocalBounds().width;
    // pText->getText()->setPosition();
    // vecScores.at(i)->setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - fWidth / 2, pText->getText()->getPosition().y + 30.f * (i + 1)));
    // vecScores.at(i)->setEnabled(true);
    // this->attachChild(vecScores.at(i));
    // vecTopTimes.at(i)->initialize();
    // }
}

// Text *views::LeaderboardScreen::copyText(Text *pReference, std::string strText, float fScale)
// {
//     Text *pText = new Text(this->strName + " Text",
//                            strText,
//                            FontManager::getInstance()->getFont(FontType::DEFAULT),
//                            fScale);

//     this->attachChild(pText);

//     pText->getText()->setStyle(pReference->getText()->getStyle());
//     pText->getText()->setOutlineThickness(pReference->getText()->getOutlineThickness());
//     pText->getText()->setOutlineColor(pReference->getText()->getOutlineColor());
//     pText->getText()->setFillColor(pReference->getText()->getFillColor());

//     pText->setPosition(pReference->getPosition());

//     return pText;
// }

void LeaderboardScreen::loadScores()
{
    std::ifstream scores("File/scores.txt");

    if (!scores.is_open())
    {
        std::cout << "scores.txt does not exist" << std::endl;
        return;
    }

    std::vector<int> vecFile;
    std::string readFile;
    while (std::getline(scores, readFile))
    {
        vecFile.push_back(std::stoi(readFile));
    }

    scores.close();
    std::sort(vecFile.begin(), vecFile.end(), std::greater<int>());

    if (this->vecScores.size() != 5)
    {
        std::cout << "vecTop does not have 5 entries" << std::endl;
        return;
    }

    for (size_t i = 0; i < std::min(5, (int)vecFile.size()); i++)
    {
        this->vecScores.at(i)->setText(std::to_string(vecFile.at(i)));
        // std::cout << "reading: " << vecScores.at(i) << std::endl;
        // int ms = (int)(vecScores.at(i) * 1000.f);

        // int h = ms / (1000 * 60 * 60);
        // ms -= h * (1000 * 60 * 60);

        // int m = ms / (1000 * 60);
        // ms -= m * (1000 * 60);

        // int s = ms / 1000;
        // ms -= s * 1000;

        // std::stringstream CStream;
        // CStream << std::setfill('0') << std::setw(2) << m << std::setw(2) << s;
        // std::string strTime = CStream.str();
        // std::cout << "strTime size:" << strTime.size() << std::endl;

        // for (int j = 0; j < strTime.length(); j++)
        //     vecScores.at(i).at(j)->setText(std::string(1, strTime.at(j)));
    }
}

void LeaderboardScreen::onClick(Button *pButton)
{
    if (pButton->getName().find("Return Button") != std::string::npos)
    {
        this->pReturn->setColor(sf::Color::White);
    }
}

void LeaderboardScreen::onHover(Button *pButton)
{
    if (pButton->getName().find("Return Button") != std::string::npos)
        this->pReturn->setColor(sf::Color::Green);
}

void LeaderboardScreen::onRelease(Button *pButton)
{
    if (pButton->getName().find("Return Button") != std::string::npos)
    {
        std::cout << "[LEADERBOARD RETURN]" << std::endl;

        if (ViewManager::getInstance()->getView(ViewTag::TITLE_SCREEN))
            ViewManager::getInstance()->getView(ViewTag::TITLE_SCREEN)->setEnabled(true);
        else
            std::cout << "tutke screen not exist" << std::endl;

        this->setEnabled(false);
        // SceneManager::getInstance()->loadScene(SceneTag::GAME_MENU);
    }
}

void LeaderboardScreen::reset(Button *pButton)
{
    if (pButton->getName().find("Return Button") != std::string::npos)
    {
        this->pReturn->setColor(sf::Color::Black);
    }
}