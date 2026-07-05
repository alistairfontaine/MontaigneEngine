#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "AssetLoader.hpp"
#include "Shader.hpp"
#include "MontaigneMath.hpp"

struct Entity {
    Mesh mesh; Vec3 position; float speed; float velocity = 0.0f;
    Entity(Mesh m, Vec3 pos, float s) : mesh(m), position(pos), speed(s) {}

    void Update() {
        velocity -= 0.002f;
        position.y += velocity;
        if (position.y < -2.0f) { position.y = -2.0f; velocity = 0.0f; }
    }

    void Draw(Shader& shader) {
        Mat4 model = Mat4::Translation(position.x, position.y, position.z);
        shader.setMat4("model", model.m);

        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
        // Using 5 floats: 3 for Position, 2 for TexCoords
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
    }
};
#endif
