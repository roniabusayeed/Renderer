#include <glad/glad.h>
#include "VertexBuffer.h"
#include "DebugUtils.h"

VertexBuffer::VertexBuffer(const void* data, size_t size)
{
    GLCall(glGenBuffers(1, &m_id));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_id));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
