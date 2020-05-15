#pragma once

#include <glad/glad.h>
#include <vector>
#include "DebugUtils.h"

struct VertexBufferElement
{
    unsigned int count;
    unsigned int type;
    unsigned int normalized;

    inline static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:           return sizeof(GLfloat);
            case GL_UNSIGNED_INT:    return sizeof(GLuint);
            case GL_UNSIGNED_BYTE:   return sizeof(GLubyte);
        }
        // Need to support more types?
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride;
public:
    VertexBufferLayout();
    inline unsigned int GetStride()const { return m_stride; }
    inline const std::vector<VertexBufferElement>& GetElements()const { return m_elements; }

    template<typename T>
    void Push(unsigned int count)
    {
        static_assert(false);
    }
    
    template<>
    void Push<float>(unsigned int count)
    {
        m_elements.push_back({ count, GL_FLOAT, GL_FALSE });
        m_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }
    
    template<>
    void Push<unsigned int>(unsigned int count)
    {
        m_elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
        m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void Push<unsigned char>(unsigned int count)
    {
        m_elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
        m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }
};
