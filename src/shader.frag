#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in float AmbientOcclusion;

uniform sampler2D texture1;
uniform vec3 viewPos;
uniform vec3 lightPos;

void main() {
    float dayFactor = max(normalize(lightPos).y, 0.0);
    float ambientStrength = 0.05 + (0.20 * dayFactor);
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    if (lightPos.y < 0.0) diff = 0.0;
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

    float specularStrength = 0.6;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    if (lightPos.y < 0.0) spec = 0.0;
    vec3 specular = specularStrength * spec * vec3(1.0, 1.0, 1.0);

    vec4 texColor = texture(texture1, TexCoord);
    vec3 baseMaterialColor = max(texColor.rgb, vec3(0.15, 0.15, 0.15));

    vec3 lighting = (ambient + diffuse + specular) * AmbientOcclusion;
    vec3 finalColor = lighting * baseMaterialColor;

    FragColor = vec4(finalColor, texColor.a);
}
