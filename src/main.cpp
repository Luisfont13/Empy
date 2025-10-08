#include <glad.h>
#include <GLFW/glfw3.h>

// Nuestros módulos
#include "core/renderer/renderer.hpp"
#include "core/buffer/vertex_buffer.hpp"
#include "core/buffer/index_buffer.hpp"
#include "core/buffer/vertex_array.hpp"
#include "core/shader/shader.hpp"
#include "core/texture/texture.hpp"
#include "core/types/types.hpp"

#include <iostream>

// Variables globales para input
bool keys[1024];
Engine::Vec3 cameraPos = Engine::Vec3(0.0f, 0.0f, 3.0f);
Engine::Vec3 cameraFront = Engine::Vec3(0.0f, 0.0f, -1.0f);
Engine::Vec3 cameraUp = Engine::Vec3(0.0f, 1.0f, 0.0f);

// Funciones de callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main() {
    // 1. Inicializar GLFW
    if (!glfwInit()) {
        std::cerr << "❌ No se pudo inicializar GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. Crear ventana
    GLFWwindow* window = glfwCreateWindow(800, 600, "Mi Motor Gráfico Supremo", nullptr, nullptr);
    if (!window) {
        std::cerr << "❌ No se pudo crear la ventana\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // 3. Inicializar Renderer
    Engine::Renderer renderer;
    if (!renderer.initialize(window)) {
        std::cerr << "❌ No se pudo inicializar el Renderer\n";
        glfwTerminate();
        return -1;
    }

    // 4. Crear vértices e índices para un triángulo
    float vertices[] = {
        // Posición     // UV
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,  // Vértice inferior izquierdo
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,  // Vértice inferior derecho
         0.0f,  0.5f, 0.0f,   0.5f, 1.0f   // Vértice superior
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    // 5. Crear buffers
    Engine::VertexBuffer vb(vertices, 3 * 5 * sizeof(float));
    Engine::IndexBuffer ib(indices, 3);

    Engine::VertexArray va;
    va.addVertexBuffer(vb);
    va.setIndexBuffer(ib);

    // 6. Crear shader
    Engine::Shader shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");

    // 7. Crear textura
    Engine::Texture texture("assets/textures/test.png");

    // 8. Bucle principal
    while (!glfwWindowShouldClose(window)) {
        // Input
        if (keys[GLFW_KEY_ESCAPE])
            glfwSetWindowShouldClose(window, true);

        // Render
        renderer.clear();  // Limpiar pantalla

        // Activar shader, textura y buffers
        shader.use();
        texture.bind();
        va.bind();

        // Dibujar
        glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);

        // Presentar frame
        renderer.present();

        // Poll events
        glfwPollEvents();
    }

    renderer.shutdown();
    glfwTerminate();
    return 0;
}

// Callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    // Manejar movimiento del mouse aquí
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    // Manejar scroll aquí
}