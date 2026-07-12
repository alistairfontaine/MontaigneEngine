#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <GL/glew.h>
#include "Mesh.hpp"
#include "MontaigneMath.hpp"
#include "Shader.hpp"
#include "Collision.hpp"

struct Entity {
    int id;
    Mesh mesh;
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
    GLuint textureID;

    // Isolated kinematic states for object-to-object physics simulations
    Vec3 velocity;
    bool isGrounded;
    float lifetime; // Track how long this cube has been alive in seconds

    // Phase P: Face shadow tracking attributes (0.3f = deep corner cave, 1.0f = clear sky open air)
    // Indexes: 0 = Top, 1 = Bottom, 2 = North (+Z), 3 = South (-Z), 4 = East (+X), 5 = West (-X)
    float faceOcclusion[6];

    Entity(int uniqueID, Mesh m, Vec3 pos, GLuint tex)
        : id(uniqueID), mesh(m), position(pos), rotation{0.0f, 0.0f, 0.0f}, scale{1.0f, 1.0f, 1.0f}, textureID(tex),
          velocity{0.0f, 0.0f, 0.0f}, isGrounded(false), lifetime(0.0f) {
              faceOcclusion[0] = 1.0f; faceOcclusion[1] = 1.0f; faceOcclusion[2] = 1.0f;
              faceOcclusion[3] = 1.0f; faceOcclusion[4] = 1.0f; faceOcclusion[5] = 1.0f;
          }


    // Computes bounding volume extents from center-point translations
    AABB GetBoundingBox() const {
        AABB box;
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

        // Phase P: Pass localized neighborhood face occlusion scalars up to shader handles
        shader.setFloat("ao_top_bot_north", faceOcclusion[0]);
        shader.setFloat("ao_south_east_west", faceOcclusion[3]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glBindVertexArray(mesh.vao);
        glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
        glBindVertexArray(0);
    }
};

#endif // ENTITY_HPP
