
#pragma once

#include <memory>

namespace prime::core {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> createScope(Args&& ...args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    
} // namespace prime::core