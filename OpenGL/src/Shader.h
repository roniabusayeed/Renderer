#pragma once
#include <string>
#include <unordered_map>

struct ShaderSource
{
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
};

class Shader
{
private:
    unsigned int m_id;
    mutable std::unordered_map<std::string, int> m_uniformLocationCache;
public:
    Shader(const std::string& filePath);
    ~Shader();
    void Bind()const;
    void Unbind()const;
    
    void SetUniform(const std::string& uniformName, int value);
    void SetUniform(const std::string& uniformName, float value);
private:
    static ShaderSource ParseShader(const std::string& filePath);
    static unsigned int CompileShader(unsigned int type, const std::string& source);
    int GetUniformLocation(const std::string& uniformName)const;
};

