#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "Mesh.hpp"
#include "Shader.hpp"
#include "MontaigneMath.hpp"
#include <vector>
#include <cmath>

struct Entity {
    Mesh mesh; Vec3 position; float velocity = 0.0f;
    Entity(Mesh m, Vec3 pos) : mesh(m), position(pos) {}

    void Update(std::vector<Entity>& scene) {
        velocity -= 0.003f; // Apply Gravity
        position.y += velocity;

        // Floor Collision Resolution
        if (position.y < -2.0f) {
            position.y = -2.0f;
            velocity = 0.0f;
        }

        // Entity vs Entity AABB Collision Resolution (Stacking)
        for (auto& other : scene) {
            if (&other == this) continue; // Skip self

            // Absolute distance checking across bounds (Cube extent size is 1.0f)
            bool intersectX = std::abs(position.x - other.position.x) < 0.95f;
            bool intersectZ = std::abs(position.z - other.position.z) < 0.95f;
            bool intersectY = std::abs(position.y - other.position.y) < 1.00f;

            if (intersectX && intersectY && intersectZ) {
                // If this object is falling downwards onto the top of another entity
                if (velocity < 0.0f && position.y > other.position.y) {
                    position.y = other.position.y + 1.0f; // Rest exactly on top face
                    velocity = 0.0f;
                }
            }
        }
    }

    void Draw(Shader& shader) {
        Mat4 model = Mat4::Translation(position.x, position.y, position.z);
        shader.setMat4("m", model.m);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
    }
};
#endif
