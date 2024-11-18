#pragma once

#include <memory>

namespace prime {

	/** @brief unique pointer. */
	template <typename T>
	using Scope = std::unique_ptr<T>;

	/** @brief make a shared pointer. */
	template <typename TClass, typename... TArgs>
	constexpr Scope<TClass> create_scope(TArgs &&...args)
	{
		return std::make_unique<TClass>(std::forward<TArgs>(args)...);
	}
}
