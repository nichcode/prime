
#pragma once

#include "entity.h"
#include "prime/renderer/renderer2d.h"
#include "prime/core/physics2d.h"

namespace prime::scene {

    struct SceneHandle;
    
    class Scene2D
    {
    private:
        SceneHandle* m_Handle;
        u32 m_MainCamera2D;
        void* m_World = nullptr;

        friend class Entity;

    public:
        Scene2D();
        ~Scene2D();

		Entity createEntity();
		void deleteEntity(Entity entity);

        void initPhysics();
        void stepPhysics(f32 delta_time = 1.0f / 60.0f);

        void render(renderer::Renderer2D& renderer);
    };
    
} // namespace prime::scene
