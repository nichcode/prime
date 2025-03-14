
#include "prime/scene/entity.h"
#include "prime_utils.h"
#include "prime/scene/components.h"
#include "prime/core/logger.h"

namespace prime::scene {

    b8 Entity::isAlive() const
    {
        return m_Scene->registry.valid((entt::entity)m_ID);
    }

    // transform
    template<> Transform&
    Entity::addComponent<Transform>()
	{
        entt::entity id = (entt::entity)m_ID;
        b8 has =  m_Scene->registry.has<Transform>(id);
        PRIME_ASSERT_MSG(!has, "entity already has Transform!");
        Transform& component = m_Scene->registry.emplace<Transform>(id);
		return component;
	}

    template<> Transform&
    Entity::getComponent<Transform>()
	{
        entt::entity id = (entt::entity)m_ID;
        b8 has =  m_Scene->registry.has<Transform>(id);
        PRIME_ASSERT_MSG(has, "entity does not have Transform!");
		return m_Scene->registry.get<Transform>(id);
	}

    template<> b8
    Entity::hasComponent<Transform>()
	{
        entt::entity id = (entt::entity)m_ID;
        return m_Scene->registry.has<Transform>(id);
	}

    template<> void
    Entity::removeComponent<Transform>()
	{
        entt::entity id = (entt::entity)m_ID;
        b8 has =  m_Scene->registry.has<Transform>(id);
        PRIME_ASSERT_MSG(has, "entity does not have Transform!");
        return m_Scene->registry.remove<Transform>(id);
	}

    // sprite renderer
    template<> SpriteRenderer&
    Entity::addComponent<SpriteRenderer>()
	{
        entt::entity id = (entt::entity)m_ID;
        b8 has =  m_Scene->registry.has<SpriteRenderer>(id);
        PRIME_ASSERT_MSG(!has, "entity already has SpriteRenderer!");
        SpriteRenderer& component = m_Scene->registry.emplace<SpriteRenderer>(id);
		return component;
	}

    template<> SpriteRenderer&
    Entity::getComponent<SpriteRenderer>()
	{
        entt::entity id = (entt::entity)m_ID;
        b8 has =  m_Scene->registry.has<SpriteRenderer>(id);
        PRIME_ASSERT_MSG(has, "entity does not have SpriteRenderer!");
		return m_Scene->registry.get<SpriteRenderer>(id);
	}

    template<> b8
    Entity::hasComponent<SpriteRenderer>()
	{
        entt::entity id = (entt::entity)m_ID;
        return m_Scene->registry.has<SpriteRenderer>(id);
	}

    template<> void
    Entity::removeComponent<SpriteRenderer>()
	{
        entt::entity id = (entt::entity)m_ID;
        b8 has =  m_Scene->registry.has<SpriteRenderer>(id);
        PRIME_ASSERT_MSG(has, "entity does not have SpriteRenderer!");
        return m_Scene->registry.remove<SpriteRenderer>(id);
	}

    // camera2D component
    template<> Camera2DComponent&
    Entity::addComponent<Camera2DComponent>()
	{
        entt::entity id = (entt::entity)m_ID;
        b8 has =  m_Scene->registry.has<Camera2DComponent>(id);
        PRIME_ASSERT_MSG(!has, "entity already has Camera2DComponent!");
        Camera2DComponent& component = m_Scene->registry.emplace<Camera2DComponent>(id);
		return component;
	}

    template<> Camera2DComponent&
    Entity::getComponent<Camera2DComponent>()
	{
        entt::entity id = (entt::entity)m_ID;
        b8 has =  m_Scene->registry.has<Camera2DComponent>(id);
        PRIME_ASSERT_MSG(has, "entity does not have Camera2DComponent!");
		return m_Scene->registry.get<Camera2DComponent>(id);
	}

    template<> b8
    Entity::hasComponent<Camera2DComponent>()
	{
        entt::entity id = (entt::entity)m_ID;
        return m_Scene->registry.has<Camera2DComponent>(id);
	}

    template<> void
    Entity::removeComponent<Camera2DComponent>()
	{
        entt::entity id = (entt::entity)m_ID;
        b8 has =  m_Scene->registry.has<Camera2DComponent>(id);
        PRIME_ASSERT_MSG(has, "entity does not have Camera2DComponent!");
        return m_Scene->registry.remove<Camera2DComponent>(id);
	}

     // rigidbody2d
    template<> RigidBody2D&
    Entity::addComponent<RigidBody2D>()
	{
        entt::entity id = (entt::entity)m_ID;
        b8 has =  m_Scene->registry.has<RigidBody2D>(id);
        PRIME_ASSERT_MSG(!has, "entity already has RigidBody2D!");
        RigidBody2D& component = m_Scene->registry.emplace<RigidBody2D>(id);
		return component;
	}

    template<> RigidBody2D&
    Entity::getComponent<RigidBody2D>()
	{
        entt::entity id = (entt::entity)m_ID;
        b8 has =  m_Scene->registry.has<RigidBody2D>(id);
        PRIME_ASSERT_MSG(has, "entity does not have RigidBody2D!");
		return m_Scene->registry.get<RigidBody2D>(id);
	}

    template<> b8
    Entity::hasComponent<RigidBody2D>()
	{
        entt::entity id = (entt::entity)m_ID;
        return m_Scene->registry.has<RigidBody2D>(id);
	}

    template<> void
    Entity::removeComponent<RigidBody2D>()
	{
        entt::entity id = (entt::entity)m_ID;
        b8 has =  m_Scene->registry.has<RigidBody2D>(id);
        PRIME_ASSERT_MSG(has, "entity does not have RigidBody2D!");
        return m_Scene->registry.remove<RigidBody2D>(id);
	}
    
    // boxcollider
    template<> BoxCollider2D&
    Entity::addComponent<BoxCollider2D>()
	{
        entt::entity id = (entt::entity)m_ID;
        b8 has =  m_Scene->registry.has<BoxCollider2D>(id);
        PRIME_ASSERT_MSG(!has, "entity already has BoxCollider2D!");
        BoxCollider2D& component = m_Scene->registry.emplace<BoxCollider2D>(id);
		return component;
	}

    template<> BoxCollider2D&
    Entity::getComponent<BoxCollider2D>()
	{
        entt::entity id = (entt::entity)m_ID;
        b8 has =  m_Scene->registry.has<BoxCollider2D>(id);
        PRIME_ASSERT_MSG(has, "entity does not have BoxCollider2D!");
		return m_Scene->registry.get<BoxCollider2D>(id);
	}

    template<> b8
    Entity::hasComponent<BoxCollider2D>()
	{
        entt::entity id = (entt::entity)m_ID;
        return m_Scene->registry.has<BoxCollider2D>(id);
	}

    template<> void
    Entity::removeComponent<BoxCollider2D>()
	{
        entt::entity id = (entt::entity)m_ID;
        b8 has =  m_Scene->registry.has<BoxCollider2D>(id);
        PRIME_ASSERT_MSG(has, "entity does not have BoxCollider2D!");
        return m_Scene->registry.remove<BoxCollider2D>(id);
	}
    
} // namespace prime::scene
