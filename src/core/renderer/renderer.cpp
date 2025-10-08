#include "renderer.hpp"
#include <iostream>
#include <vector>

namespace Engine {

bool Renderer::initialize(GLFWwindow* window) {
    m_window = window;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "❌ No se pudieron cargar las funciones de OpenGL con GLAD\n";
        return false;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    // Crear buffers para batch rendering
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    glGenBuffers(1, &m_InstanceVBO);

    glBindVertexArray(m_VAO);

    // Vértices del cuadrado
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // Vértice inferior izquierdo
         0.5f, -0.5f, 0.0f,  // Vértice inferior derecho
         0.5f,  0.5f, 0.0f,  // Vértice superior derecho
        -0.5f,  0.5f, 0.0f   // Vértice superior izquierdo
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Instancing: atributos por instancia
    glBindBuffer(GL_ARRAY_BUFFER, m_InstanceVBO);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Engine::Mat4), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);  // Este atributo cambia por instancia

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    std::cout << "✅ Renderer inicializado correctamente\n";
    return true;
}

void Renderer::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawSquare(const Vec3& position, const Color& color) {
    RenderCommand cmd;
    cmd.VAO = m_VAO;
    cmd.indexCount = 6;
    cmd.mode = GL_TRIANGLES;
    cmd.instanceCount = 1;

    // Matriz de transformación simple (posición)
    cmd.transform = Mat4();
    cmd.transform.data[12] = position.x;  // x
    cmd.transform.data[13] = position.y;  // y
    cmd.transform.data[14] = position.z;  // z

    cmd.color = color;

    m_Commands.push_back(cmd);
}

void Renderer::flush() {
    glBindVertexArray(m_VAO);

    for (const auto& cmd : m_Commands) {
        glBindBuffer(GL_ARRAY_BUFFER, m_InstanceVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Mat4), &cmd.transform, GL_DYNAMIC_DRAW);

        glDrawElementsInstanced(cmd.mode, cmd.indexCount, GL_UNSIGNED_INT, 0, cmd.instanceCount);
    }

    glBindVertexArray(0);
    m_Commands.clear();
}

void Renderer::present() {
    glfwSwapBuffers(m_window);
}

void Renderer::shutdown() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    glDeleteBuffers(1, &m_InstanceVBO);
    std::cout << "_renderer apagado_\n";
}

} // namespace Engine