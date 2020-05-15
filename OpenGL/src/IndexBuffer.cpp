#include <glad/glad.h>
#include "IndexBuffer.h"
#include "DebugUtils.h"

IndexBuffer::IndexBuffer(const unsigned int* data, size_t count)
    : m_count(count)
{
    ASSERT(sizeof(GLuint) == sizeof(unsigned int));

    GLCall(glGenBuffers(1, &m_id));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_id));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::GetIndexType() const
{
    return GL_UNSIGNED_INT;
}
