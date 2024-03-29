#ifndef CORE_VERTEX_BUFFER_HPP
#define CORE_VERTEX_BUFFER_HPP

#include "pch.hpp" // IWYU pragma: export

namespace Core {
/**
 * @brief Wrapper for OpenGL Vertex Buffer Object (a.k.a `GL_ARRAY_BUFFER`)
 */
class VertexBuffer {
public:
    enum DrawingType { STATIC, DYNAMIC, STREAM };
    VertexBuffer(const std::vector<float> &vertices,
                 unsigned int componentCount, DrawingType type = STATIC);
    VertexBuffer(const VertexBuffer &) = delete;
    VertexBuffer(VertexBuffer &&other);

    ~VertexBuffer();

    VertexBuffer &operator=(const VertexBuffer &) = delete;
    VertexBuffer &operator=(VertexBuffer &&other);

    unsigned int GetComponentCount() const { return m_ComponentCount; }
    GLenum GetType() const { return m_Type; }

    void Bind() const;
    void Unbind() const;
    
    template <class T>
    void ModifyBufferData(int size, std::vector<T> data);

private:
    GLuint m_BufferId;
    unsigned int m_ComponentCount;
    GLenum m_Type = GL_FLOAT;
};
} // namespace Core
#endif
