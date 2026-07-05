#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform vec3 viewPos;

void main() {
    // 1. Ambient lighting (constant environmental fill)
    float ambientStrength = 0.25;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

    // 2. Diffuse lighting (directional shading)
    vec3 norm = normalize(Normal);
    vec3 lightPos = vec3(3.0, 5.0, 4.0); // Light source positions
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

    // 3. Specular lighting (glistening shine)
    float specularStrength = 0.6;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16); // Lowered to 16 for a wider, more visible glare
    vec3 specular = specularStrength * spec * vec3(1.0, 1.0, 1.0);

    // Look up your custom artwork texture pixel values
    vec4 texColor = texture(texture1, TexCoord);

    // BLENDING MIX: If the texture pixel is pure black (0,0,0), lift it slightly to a dark grey
    // baseline so it can catch shadows and specular glint reflections clearly.
    vec3 baseMaterialColor = max(texColor.rgb, vec3(0.15, 0.15, 0.15));

    // Combine lighting models over your texture layout
    vec3 finalColor = (ambient + diffuse + specular) * baseMaterialColor;

    FragColor = vec4(finalColor, texColor.a);
}
