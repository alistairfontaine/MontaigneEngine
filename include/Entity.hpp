#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "AssetLoader.hpp"
#include "Shader.hpp"
#include "MontaigneMath.hpp"

struct Entity {
    Mesh mesh;
    Vec3 position;
    float speed;
    Entity(Mesh m, Vec3 pos, float s) : mesh(m), position(pos), speed(s) {}

    void Draw(Shader& shader, float time) {
        Mat4 model = Mat4::Translation(position.x, position.y + sin(time * speed), position.z);
        shader.setMat4("model", model.m);

        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
        int stride = 5 * sizeof(float); // Back to 5: 3 pos, 2 UV

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
    }
};
#endif
