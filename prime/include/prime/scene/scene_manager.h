
#pragma once

#include "scene2d.h"

namespace prime::scene {

    class SceneManager
    {
    public:
        static core::Ref<Scene2D> createScene2D();
    };
    
} // namespace prime::scene
