#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <GL/glew.h>
#include "Mesh.hpp"
#include "MontaigneMath.hpp"
#include "Shader.hpp"
#include "Collision.hpp"

struct Entity {
    Mesh mesh;
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
    GLuint textureID;

    Entity(Mesh m, Vec3 pos, GLuint tex)
        : mesh(m), position(pos), rotation{0.0f, 0.0f, 0.0f}, scale{1.0f, 1.0f, 1.0f}, textureID(tex) {}

    // Computes bounding volume extents from center-point translations
    AABB GetBoundingBox() const {
        AABB box;
        // Basic model assumes a 1-unit baseline source model radius bounds
        box.minBounds = Vec3{ position.x - scale.x, position.y - scale.y, position.z - scale.z };
        box.maxBounds = Vec3{ position.x + scale.x, position.y + scale.y, position.z + scale.z };
        return box;
    }

    void Draw(Shader& shader) {
        shader.use();

        Mat4 translationMatrix = Mat4::Translation(position.x, position.y, position.z);
        Mat4 scaleMatrix       = Mat4::Scaling(scale.x, scale.y, scale.z);

        Mat4 rotX = Mat4::RotationX(rotation.x);
        Mat4 rotY = Mat4::RotationY(rotation.y);
        Mat4 rotZ = Mat4::RotationZ(rotation.z);
        Mat4 rotationMatrix    = rotZ * rotY * rotX;

        Mat4 modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

        shader.setMat4("model", modelMatrix.m);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glBindVertexArray(mesh.vao);
        glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
        glBindVertexArray(0);
    }
};

#endif // ENTITY_HPP
