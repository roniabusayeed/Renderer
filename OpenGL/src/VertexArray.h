#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
    unsigned int m_id;
public:
    VertexArray();
    ~VertexArray();
    void Bind()const;
    void Unbind()const;
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};

