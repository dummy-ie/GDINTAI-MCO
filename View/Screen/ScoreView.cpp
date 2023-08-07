#include "ScoreView.hpp"

using namespace views;

ScoreView::ScoreView(std::string strName) : View(ViewTag::SCORE_VIEW, strName) {
    ViewManager::getInstance()->registerView(this);
    this->nPlayerKills = 0;
    this->nPlayerBaseKills = 0;
    this->nEnemyKills = 0;
    this->nEnemyBaseKills = 0;
}

ScoreView::~ScoreView() {}

void ScoreView::initialize() {
    float nOffset = 20.f;
    this->txtPlayerKill = new Text(this->strName + " Player Kill", "0", FontManager::getInstance()->getFont(FontType::DEFAULT), 16);
    this->txtPlayerBase = new Text(this->strName + " Player Base Kill", "0", FontManager::getInstance()->getFont(FontType::DEFAULT), 16);
    this->txtEnemyKill = new Text(this->strName + " Enemy Kill", "0", FontManager::getInstance()->getFont(FontType::DEFAULT), 16);
    this->txtEnemyBase = new Text(this->strName + " Enemy Base Kill", "0", FontManager::getInstance()->getFont(FontType::DEFAULT), 16);
    this->attachChild(this->txtPlayerKill);
    this->attachChild(this->txtPlayerBase);
    this->attachChild(this->txtEnemyKill);
    this->attachChild(this->txtEnemyBase);
    sf::Color CColor = sf::Color::Green;
    CColor.a = 127;
    this->txtPlayerKill->getText()->setOutlineThickness(1.0f);
    this->txtPlayerKill->getText()->setOutlineColor(CColor);
    this->txtPlayerBase->getText()->setOutlineThickness(1.0f);
    this->txtPlayerBase->getText()->setOutlineColor(CColor);
    this->txtPlayerBase->setPosition(sf::Vector2f(0.f, nOffset));
    CColor = sf::Color::Red;
    CColor.a = 127;
    this->txtEnemyKill->getText()->setOutlineThickness(1.0f);
    this->txtEnemyKill->getText()->setOutlineColor(CColor);
    this->txtEnemyKill->setPosition(sf::Vector2f(0.f, nOffset * 2));
    this->txtEnemyBase->getText()->setOutlineThickness(1.0f);
    this->txtEnemyBase->getText()->setOutlineColor(CColor);
    this->txtEnemyBase->setPosition(sf::Vector2f(0.f, nOffset * 3));
    
}

void ScoreView::incrementPlayerKill() {
    this->nPlayerKills++;
    this->txtPlayerKill->setText(std::to_string(this->nPlayerKills));
}

void ScoreView::incrementPlayerBaseKill() {
    this->nPlayerBaseKills++;
    this->txtPlayerBase->setText(std::to_string(this->nPlayerBaseKills));
}

void ScoreView::incrementEnemyKill() {
    this->nEnemyKills++;
    this->txtEnemyKill->setText(std::to_string(this->nEnemyKills));
}

void ScoreView::incrementEnemyBaseKill() {
    this->nEnemyBaseKills++;
    this->txtEnemyBase->setText(std::to_string(this->nEnemyBaseKills));
}