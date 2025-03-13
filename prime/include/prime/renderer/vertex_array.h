
#pragma once

#include "layout.h"
#include "prime/core/ref.h"

namespace prime::renderer {

    class VertexArray
    {
    public:
        virtual ~VertexArray() {}

        virtual void setLayout(const Layout& layout) = 0;

        virtual void bind() const = 0;
        virtual void unBind() const = 0;
    };

} // namespace prime::renderer  
