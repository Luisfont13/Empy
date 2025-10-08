#include "shader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


namespace Engine {

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexSource = loadFile(vertexPath);
    std::string fragmentSource = loadFile(fragmentPath);

    m_RendererID = createShader(vertexSource, fragmentSource);
}

Shader::~Shader() {
    glDeleteProgram(m_RendererID);
}

std::string Shader::loadFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "❌ No se pudo abrir el archivo: " << path << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    return content;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Verificar errores
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cerr << "❌ Error compilando shader:\n" << message << std::endl;
        glDeleteShader(id);
        delete[] message;
        return 0;
    }

    return id;
}

unsigned int Shader::createShader(const std::string& vertexSource, const std::string& fragmentSource) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // Limpiar
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::use() const {
    glUseProgram(m_RendererID);
}

void Shader::setUniform(const std::string& name, float value) {
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location != -1) {
        glUniform1f(location, value);
    }
}

void Shader::setUniform(const std::string& name, int value) {
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location != -1) {
        glUniform1i(location, value);
    }
}

void Shader::setUniform(const std::string& name, float x, float y, float z) {
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location != -1) {
        glUniform3f(location, x, y, z);
    }
}

} // namespace Engine