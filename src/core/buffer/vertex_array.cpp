#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"

namespace Engine {

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::addVertexBuffer(const VertexBuffer& vb) {
    glBindVertexArray(m_RendererID);
    vb.bind();

    // Suponemos vértices de 3 floats (x, y, z)
    glVertexAttribPointer(m_VertexBufferIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(m_VertexBufferIndex);
    m_VertexBufferIndex++;
}

void VertexArray::setIndexBuffer(const IndexBuffer& ib) {
    glBindVertexArray(m_RendererID);
    ib.bind();
}

void VertexArray::bind() const {
    glBindVertexArray(m_RendererID);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

} // namespace Engine