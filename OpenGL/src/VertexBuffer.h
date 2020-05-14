#pragma once
class VertexBuffer
{
private:
    unsigned int m_id;
public:
    VertexBuffer(size_t size, const void* data);
    ~VertexBuffer();
    void bind()const;
    void unbind()const;
};

