#include "Core/VertexBuffer.hpp"

namespace Core {
VertexBuffer::VertexBuffer(const std::vector<float> &vertices,
                           unsigned int componentCount, DrawingType type)
    : m_ComponentCount(componentCount) {
    /*
     * There are three drawing types,
     * Static: set only once and used many times.
     * Dynamic: the data is changed a lot and used many times.
     * Stream: the data is set only once and used by the GPU at most a few times
     */

    glGenBuffers(1, &m_BufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
    switch (type) {
    case (STATIC):
        glBufferData(GL_ARRAY_BUFFER,
                     static_cast<GLsizeiptr>(vertices.size() * sizeof(GLfloat)),
                     vertices.data(), GL_STATIC_DRAW);
        break;
    case (DYNAMIC):
        glBufferData(GL_ARRAY_BUFFER,
                     static_cast<GLsizeiptr>(vertices.size() * sizeof(GLfloat)),
                     vertices.data(), GL_DYNAMIC_DRAW);
        break;
    case (STREAM):
        glBufferData(GL_ARRAY_BUFFER,
                     static_cast<GLsizeiptr>(vertices.size() * sizeof(GLfloat)),
                     vertices.data(), GL_STREAM_DRAW);
        break;
    }
}

VertexBuffer::VertexBuffer(VertexBuffer &&other) {
    m_BufferId = other.m_BufferId;
    other.m_BufferId = 0;

    m_ComponentCount = std::move(other.m_ComponentCount);
    m_Type = std::move(other.m_Type);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_BufferId);
}

VertexBuffer &VertexBuffer::operator=(VertexBuffer &&other) {
    m_BufferId = other.m_BufferId;
    other.m_BufferId = 0;

    m_ComponentCount = std::move(other.m_ComponentCount);
    m_Type = std::move(other.m_Type);

    return *this;
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
} // namespace Core
