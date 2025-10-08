#pragma once

#include <glad.h>
#include <GLFW/glfw3.h>

namespace Engine {

class Renderer {
public:
    // Inicializa el renderizador
    bool initialize(GLFWwindow* window);

    // Limpia la pantalla
    void clear(float r = 0.1f, float g = 0.2f, float b = 0.3f, float a = 1.0f);

    // Presenta el frame (intercambia buffers)
    void present();

    // Limpia recursos
    void shutdown();

private:
    GLFWwindow* m_window = nullptr;
};

} // namespace Engine