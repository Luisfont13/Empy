#pragma once

#include <glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "types/types.hpp"

namespace Engine {

struct RenderCommand {
    unsigned int VAO;
    unsigned int indexCount;
    GLenum mode;
    unsigned int instanceCount;
    Engine::Mat4 transform;
    Engine::Color color;
};

class Renderer {
public:
    bool initialize(GLFWwindow* window);
    void clear(float r = 0.1f, float g = 0.2f, float b = 0.3f, float a = 1.0f);
    void present();
    void shutdown();

    // Funciones para dibujar formas
    void drawSquare(const Engine::Vec3& position, const Engine::Color& color = Engine::Color());
    void drawCircle(const Engine::Vec3& position, const Engine::Color& color = Engine::Color());
    void drawTriangle(const Engine::Vec3& position, const Engine::Color& color = Engine::Color());

    // Batch rendering
    void flush();  // Ejecutar todos los comandos acumulados

private:
    GLFWwindow* m_window = nullptr;
    std::vector<RenderCommand> m_Commands;

    // Buffers para batch rendering
    unsigned int m_VAO, m_VBO, m_EBO;
    unsigned int m_InstanceVBO;

    // Shaders
    unsigned int m_ShaderProgram;
};

} // namespace Engine