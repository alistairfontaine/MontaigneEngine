#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in float AmbientOcclusion; // Catch the face shadow scalar from the vertex step

uniform sampler2D texture1;
uniform vec3 viewPos;

void main() {
    float ambientStrength = 0.25;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

    vec3 norm = normalize(Normal);
    vec3 lightPos = vec3(3.0, 5.0, 4.0);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

    float specularStrength = 0.6;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    vec3 specular = specularStrength * spec * vec3(1.0, 1.0, 1.0);

    vec4 texColor = texture(texture1, TexCoord);
    vec3 baseMaterialColor = max(texColor.rgb, vec3(0.15, 0.15, 0.15));

    // Combine diffuse and ambient vectors, then smoothly bake in Ambient Occlusion shadows
    vec3 lighting = (ambient + diffuse + specular) * AmbientOcclusion;
    vec3 finalColor = lighting * baseMaterialColor;

    FragColor = vec4(finalColor, texColor.a);
}

