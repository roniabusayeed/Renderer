#include "VertexArray.h"
#include "DebugUtils.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_id));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_id));
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_id));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();

    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int stride = layout.GetStride();
    unsigned int offset = 0;
    for (unsigned int i = 0, n = elements.size(); i < n; i++)
    {
        const auto& element = elements[i];
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, stride,
            (const void*)(offset)));
        GLCall(glEnableVertexAttribArray(i));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}
