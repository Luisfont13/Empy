#include "renderer.hpp"
#include <iostream>


namespace Engine {

bool Renderer::initialize(GLFWwindow* window) {
    m_window = window;

    // Cargar funciones de OpenGL con GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "❌ No se pudieron cargar las funciones de OpenGL con GLAD\n";
        return false;
    }

    // Configurar OpenGL
    glViewport(0, 0, 800, 600);  // Ajustar según ventana
    glEnable(GL_DEPTH_TEST);     // Activar profundidad si se necesita

    std::cout << "✅ Renderer inicializado correctamente\n";
    return true;
}

void Renderer::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::present() {
    glfwSwapBuffers(m_window);
}

void Renderer::shutdown() {
    // Aquí puedes limpiar recursos si los hubiera
    std::cout << "_renderer apagado_\n";
}

} // namespace Engine