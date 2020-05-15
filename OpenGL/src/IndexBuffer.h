#pragma once

class IndexBuffer
{
private:
    unsigned int m_id;
    unsigned int m_count;
public:
    IndexBuffer(const unsigned int* data, size_t count);
    ~IndexBuffer();
    void Bind()const;
    void Unbind()const;

    inline unsigned int GetCount()const { return m_count; }
};