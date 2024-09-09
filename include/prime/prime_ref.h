#pragma once

#include <memory>

namespace prime {

	/** @brief shared pointer */
	template <typename T>
	using Ref = std::shared_ptr<T>;

	/** @brief make a shared pointer */
	template <typename TClass, typename... TArgs>
	constexpr Ref<TClass> CreateRef(TArgs &&...args)
	{
		return std::make_shared<TClass>(std::forward<TArgs>(args)...);
	}

}
