#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <GL/glew.h>
#include "Mesh.hpp"
#include "MontaigneMath.hpp"
#include "Shader.hpp"

struct Entity {
    Mesh mesh;
    Vec3 position;
    Vec3 rotation; // Euler angles in radians (X, Y, Z)
    Vec3 scale;    // Size dimensions on (X, Y, Z)
    GLuint textureID;

    Entity(Mesh m, Vec3 pos, GLuint tex)
        : mesh(m), position(pos), rotation{0.0f, 0.0f, 0.0f}, scale{1.0f, 1.0f, 1.0f}, textureID(tex) {}

    void Draw(Shader& shader) {
        shader.use();

        // 1. Calculate transformation components using our refactored math operators
        Mat4 translationMatrix = Mat4::Translation(position.x, position.y, position.z);
        Mat4 scaleMatrix       = Mat4::Scaling(scale.x, scale.y, scale.z);

        Mat4 rotX = Mat4::RotationX(rotation.x);
        Mat4 rotY = Mat4::RotationY(rotation.y);
        Mat4 rotZ = Mat4::RotationZ(rotation.z);
        Mat4 rotationMatrix    = rotZ * rotY * rotX; // Combined Euler rotation sequence

        // 2. Compute final unified Model matrix (TRS order)
        Mat4 modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

        // 3. Upload the unified matrix block to the vertex program
        shader.setMat4("model", modelMatrix.m);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glBindVertexArray(mesh.vao);
        glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
        glBindVertexArray(0);
    }
};

#endif // ENTITY_HPP
