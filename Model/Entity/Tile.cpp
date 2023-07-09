#include "Tile.hpp"

using namespace models;

Tile::Tile(std::string strName, AnimatedTexture* pTexture, sf::Vector2f CPosition) : GameObject(strName, pTexture) {
    this->CPosition = CPosition;
}

Tile::~Tile() {}

void Tile::initialize() {}