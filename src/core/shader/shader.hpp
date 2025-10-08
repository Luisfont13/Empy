#pragma once

#include <glad.h>
#include <string>

namespace Engine {

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;

    // Métodos para establecer uniforms (más adelante)
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, float x, float y, float z);

private:
    unsigned int m_RendererID;

    // Funciones auxiliares
    std::string loadFile(const std::string& path);
    unsigned int compileShader(unsigned int type, const std::string& source);
    unsigned int createShader(const std::string& vertexSource, const std::string& fragmentSource);
};

} // namespace Engine