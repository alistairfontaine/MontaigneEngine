#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform vec4 modelPos;
uniform mat4 view;
uniform mat4 projection;

void main() {
    mat4 model = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        modelPos.x, modelPos.y, modelPos.z, 1.0
    );

    // Calculate vertex position in world coordinates
    FragPos = vec3(model * vec4(aPos, 1.0));

    // Pass transformed normal direction to the fragment shader
    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
