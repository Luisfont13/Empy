#pragma once

#include <cstdint>

namespace Engine {

// Alias de tipos comunes
using Index = uint32_t;
using Vertex = float;

// Vec2
struct Vec2 {
    float x, y;

    Vec2() : x(0.0f), y(0.0f) {}
    Vec2(float x, float y) : x(x), y(y) {}
};

// Vec3
struct Vec3 {
    float x, y, z;

    Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
};

// Vec4
struct Vec4 {
    float x, y, z, w;

    Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};

// Color (RGBA)
struct Color {
    float r, g, b, a;

    Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
    Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}
};

// Rectángulo
struct Rect {
    float x, y, width, height;

    Rect() : x(0.0f), y(0.0f), width(0.0f), height(0.0f) {}
    Rect(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}
};

// Matriz 4x4 (placeholder, puedes usar GLM después)
struct Mat4 {
    float data[16];

    Mat4() {
        for (int i = 0; i < 16; i++) {
            data[i] = 0.0f;
        }
        // Identidad
        data[0] = data[5] = data[10] = data[15] = 1.0f;
    }
};

} // namespace Engine