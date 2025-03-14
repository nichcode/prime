
#pragma once

#include "entity.h"
#include "prime/renderer/renderer2d.h"

namespace prime::scene {

    struct SceneHandle;
    
    class Scene2D
    {
    private:
        SceneHandle* m_Handle;
        u32 m_MainCamera2D;
        friend class Entity;

    public:
        Scene2D();
        ~Scene2D();

		Entity createEntity();
		void deleteEntity(Entity entity);

        void render(renderer::Renderer2D& renderer);
    };
    
} // namespace prime::scene
