#include "Tile.hpp"

using namespace models;

Tile::Tile(std::string strName, AnimatedTexture* pTexture) : GameObject(strName, pTexture) {

}

Tile::~Tile() {}

void Tile::initialize() {
    this->CBounds = sf::FloatRect(0.0f, 0.0f, 16.f, 16.f);
}