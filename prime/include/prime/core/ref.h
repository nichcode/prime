
#pragma once

#include <memory>

namespace prime::core {

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Ref<T> createRef(Args&& ...args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    
} // namespace prime::core