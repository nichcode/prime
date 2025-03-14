
#include "prime/scene/scene2d.h"
#include "prime_utils.h"
#include "prime/scene/components.h"

namespace prime::scene {

    Scene2D::Scene2D()
    {
        m_Handle = new SceneHandle();
        u32 id = (u32)m_Handle->registry.create();
        Entity camera_entity = { id, m_Handle };
		camera_entity.addComponent<Transform>();
		camera_entity.addComponent<Camera2DComponent>().camera.setProjection(0.0f, 0.0f, 640.0f, 480.0f);
		m_MainCamera2D = id;
    }
    
    Scene2D::~Scene2D()
    {
        auto entities = m_Handle->registry.view<Transform>();
		for (entt::entity entity : entities)
		{
			m_Handle->registry.destroy(entity);
		}
        delete m_Handle;
    }
    
    Entity Scene2D::createEntity()
    {
        u32 id = (u32)m_Handle->registry.create();
        Entity entity(id, m_Handle);
		entity.addComponent<Transform>();
		return entity;
    }
    
    void Scene2D::deleteEntity(Entity entity)
    {
        entt::entity id = (entt::entity)entity.getHandle();
        m_Handle->registry.destroy(id);
    }
    
    void Scene2D::render(renderer::Renderer2D& renderer)
    {
        Entity camera_entity;
        if (m_Handle->registry.size() > 0) {
            camera_entity = Entity(m_MainCamera2D, m_Handle);
            renderer::Camera2D& camera = camera_entity.getComponent<Camera2DComponent>().camera;
            renderer.setCamera(camera);

            // renderer
            auto sprites = m_Handle->registry.view<Transform, SpriteRenderer>();
            for (entt::entity sprite : sprites) {
                auto [tc, sr] = sprites.get<Transform, SpriteRenderer>(sprite);
                renderer.setDrawColor(sr.color);
                if (sr.texture.get()) {
                    renderer.draw({ tc.position.x, tc.position.y }, { tc.scale.x * 50.0f, tc.scale.y * 50.0f }, sr.texture);
                }
                else {
                    renderer.draw({ tc.position.x, tc.position.y }, { tc.scale.x * 50.0f, tc.scale.y * 50.0f });
                }
            }
        }
    }
    
} // namespace prime::scene
