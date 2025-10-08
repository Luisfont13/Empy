#pragma once

#include <glad.h>
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"

namespace Engine {

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void addVertexBuffer(const VertexBuffer& vb);
    void setIndexBuffer(const IndexBuffer& ib);

    void bind() const;
    void unbind() const;

private:
    unsigned int m_RendererID;
    unsigned int m_VertexBufferIndex = 0;
};

} // namespace Engine