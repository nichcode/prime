
#pragma once

#include "prime/defines.h"

namespace prime::scene {

    class SceneHandle;

    class Entity
    {
    private:
        u32 m_ID;
        SceneHandle* m_Scene;

    public:
        Entity() = default;
        Entity(u32 handle, SceneHandle* scene) : m_ID(handle), m_Scene(scene) {}

        template<typename T> T& addComponent();
        template<typename T> T& getComponent();

        template<typename T> b8 hasComponent();
		template<typename T> void removeComponent();

        u32 getHandle() const { return m_ID; }
        b8 isAlive() const;

        b8 operator==(const Entity& other) const
		{
			return m_ID == other.m_ID && m_Scene == other.m_Scene;
		}

		b8 operator!=(const Entity& other) const
		{
			return !(*this == other);
		}
    };
    
} // namespace prime::scene
