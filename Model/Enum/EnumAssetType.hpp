#ifndef ENUM_ASSET_TYPE_HPP
#define ENUM_ASSET_TYPE_HPP

enum class AssetType : int {
    NONE = -1,
    MENU_BACKGROUND,
    PLAYER_TANK,
    ENEMY_TANK,

    BULLET,

    STONE,
    BRICK,
    BUSH,

    BULLET_EXPLOSION
};

#endif

