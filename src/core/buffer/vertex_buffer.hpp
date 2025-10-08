#pragma once

#include <glad.h>

namespace Engine {

class VertexBuffer {
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

private:
    unsigned int m_RendererID;
};

} // namespace Engine