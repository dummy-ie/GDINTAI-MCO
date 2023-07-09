#include "iostream"
#include "string"
#include "unordered_map"
#include "vector"

#include "SFML/Graphics.hpp"

#include "Model/AnimatedTexture.cpp"
#include "Model/EmptyGameObject.hpp"
#include "Model/GameObject.cpp"
#include "Model/Scene.cpp"

#include "Model/Component/Component.cpp"

#include "Model/Component/Input/ButtonInput.cpp"
#include "Model/Component/Input/GeneralInput.cpp"
#include "Model/Component/Input/TankInput.cpp"

#include "Model/Component/Renderer/Renderer.cpp"

#include "Model/Component/Script/TankControls.cpp"

#include "Model/Entity/Background.cpp"
#include "Model/Entity/Tank.cpp"
#include "Model/Entity/Tile.cpp"
//#include "Model/Entity/Map.cpp"

#include "Model/Entity/Tile/Base.cpp"
#include "Model/Entity/Tile/Wall.cpp"

#include "Model/Entity/Tank/Player.cpp"
#include "Model/Entity/Tank/Enemy.cpp"

#include "Model/Pooling/PoolableObject.cpp"

#include "Model/Scene/GameMenu.cpp"
#include "Model/Scene/GameSpace.cpp"

#include "View/Button.cpp"
#include "View/Image.cpp"
#include "View/Text.cpp"
#include "View/View.cpp"

#include "View/Screen/TitleScreen.cpp"

#include "Controller/Singleton/GameObjectManager.cpp"
#include "Controller/Singleton/FontManager.cpp"
#include "Controller/Singleton/ObjectPoolManager.cpp"
#include "Controller/Singleton/TextureManager.cpp"

#include "Controller/Pooling/GameObjectPool.cpp"

#include "Controller/System/SceneManager.cpp"
#include "Controller/System/ViewManager.cpp"

#include "Controller/Game.cpp"

int main(int argc, const char** argv) {
    std::cout << "i hate you world" << std::endl;
    Game CGame;
    CGame.run();

    return 0;
}