#include "iostream"
#include "string"
#include "unordered_map"
#include "vector"
#include "queue"
#include "cmath"

#include "SFML/Graphics.hpp"

#include "Controller/Singleton/GameObjectManager.cpp"
#include "Controller/Singleton/FontManager.cpp"
#include "Controller/Singleton/MapManager.cpp"
#include "Controller/Singleton/ObjectPoolManager.cpp"
#include "Controller/Singleton/TextureManager.cpp"

#include "Model/AnimatedTexture.cpp"
#include "Model/EmptyGameObject.cpp"
#include "Model/GameObject.cpp"
#include "Model/Scene.cpp"

#include "Model/Component/Component.cpp"

#include "Model/Component/Input/ButtonInput.cpp"
#include "Model/Component/Input/GeneralInput.cpp"
#include "Model/Component/Input/TankInput.cpp"

#include "Model/Component/Physics/Collider.cpp"

#include "Model/Component/Renderer/Renderer.cpp"

#include "Model/Component/Script/EnemyAI.cpp"
#include "Model/Component/Script/TankControls.cpp"
#include "Model/Component/Script/TankBulletMovement.cpp"
#include "Model/Component/Script/TankBulletExplode.cpp"
#include "Model/Component/Script/Killable.cpp"
#include "Model/Component/Script/Damager.cpp"
#include "Model/Component/Script/Speeder.cpp"
#include "Model/Component/Script/Timer.cpp"

#include "Model/Entity/Background.cpp"
#include "Model/Entity/Tile.cpp"
#include "Model/Entity/Map.cpp"

#include "Model/Entity/Border/Border.cpp"

#include "Model/Pooling/Tank/Tank.cpp"
#include "Model/Pooling/Tank/Player.cpp"
#include "Model/Pooling/Tank/Enemy.cpp"

#include "Model/Pooling/Item/Item.cpp"

#include "Model/Entity/Tile/Base.cpp"
#include "Model/Entity/Tile/Wall.cpp"
#include "Model/Entity/Tile/Brick.cpp"

#include "Model/Pooling/PoolableObject.cpp"

#include "Model/Pooling/Tank Bullet/TankBullet.cpp"

#include "Model/Scene/GameMenu.cpp"
#include "Model/Scene/GameSpace.cpp"

#include "View/Button.cpp"
#include "View/Image.cpp"
#include "View/Text.cpp"
#include "View/View.cpp"

#include "View/Screen/TitleScreen.cpp"
#include "View/Screen/MapSelectionScreen.cpp"
#include "View/Screen/TimerView.cpp"
#include "View/Screen/LeaderboardScreen.cpp"

#include "Controller/Pooling/GameObjectPool.cpp"
#include "Controller/Pooling/Component/Director/TankDirector.cpp"
#include "Controller/Pooling/Component/Director/ItemDirector.cpp"

#include "Controller/System/PhysicsManager.cpp"
#include "Controller/System/SceneManager.cpp"
#include "Controller/System/ViewManager.cpp"

#include "Controller/Game.cpp"

int main(int argc, const char** argv) {
    Game CGame;
    CGame.run();

    return 0;
}