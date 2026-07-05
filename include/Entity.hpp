#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <GL/glew.h>
#include "Mesh.hpp"
#include "MontaigneMath.hpp"
#include "Shader.hpp"

struct Entity {
    Mesh mesh;
    Vec3 position;
    GLuint textureID; // Added variable tracking loop to handle material maps

    Entity(Mesh m, Vec3 pos, GLuint tex) : mesh(m), position(pos), textureID(tex) {}

    void Draw(Shader& shader) {
        shader.use();

        // Pass position coordinate vectors to shader constants array
        glUniform4f(glGetUniformLocation(shader.ID, "modelPos"), position.x, position.y, position.z, 1.0f);

        // Bind the current entity texture map to texture unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glBindVertexArray(mesh.vao);
        glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
        glBindVertexArray(0);
    }
};

#endif // ENTITY_HPP
