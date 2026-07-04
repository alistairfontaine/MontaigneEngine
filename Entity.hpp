#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "Math.hpp" // Assuming you have your math library

struct Entity {
    Mat4 position;
    Mesh mesh;
    void Draw(Shader& shader) {
        shader.setMat4("model", position.m);
        // Bind mesh and draw
        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
        // ... (Vertex pointers)
        glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
    }
};
#endif
