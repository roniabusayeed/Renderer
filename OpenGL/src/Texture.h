#pragma once
#include <string>

class Texture
{
private:
    unsigned int m_id;
    int m_width, m_height, m_nrChannels;
    
public:
    Texture(const std::string& filePath);
    void Bind(unsigned int slot = 0)const;
    void Unbind()const;
    ~Texture();

    inline int GetWidth()const { return m_width; }
    inline int GetHeight()const { return m_height; }
};