
#include "prime/scene/scene_manager.h"

namespace prime::scene {

    core::Ref<Scene2D> SceneManager::createScene2D()
    {
        return core::createRef<Scene2D>();
    }
    
} // namespace prime::scene
