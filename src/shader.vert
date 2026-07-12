#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out float AmbientOcclusion;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Phase P: Explicit primitive float uniform channels matching your C++ variables
uniform float ao_top_bot_north;
uniform float ao_south_east_west;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;

    float aoFactor = 1.0;
    vec3 n = normalize(aNormal);

    // Surgically match face normal direction maps to your explicit floats
    if (n.y > 0.5)  aoFactor = ao_top_bot_north;   // Top face shadow multiplier
    if (n.y < -0.5) aoFactor = ao_top_bot_north;   // Bottom face shadow multiplier
    if (n.z > 0.5)  aoFactor = ao_top_bot_north;   // North face shadow multiplier
    if (n.z < -0.5) aoFactor = ao_south_east_west; // South face shadow multiplier
    if (n.x > 0.5)  aoFactor = ao_south_east_west; // East face shadow multiplier
    if (n.x < -0.5) aoFactor = ao_south_east_west; // West face shadow multiplier

    AmbientOcclusion = aoFactor;
}
