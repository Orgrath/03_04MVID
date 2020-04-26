#version 330 core

in vec2 uv;
in vec3 tangentLightPos;
in vec3 tangentViewPos;
in vec3 tangentFragPos;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

struct Material {
    int shininess;
};
uniform Material material;

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;

vec3 calcDirectionalLight(DirLight light, vec3 normal, vec3 viewDir, vec3 albedoMap, vec3 specularMap) {
    vec3 ambient = albedoMap * light.ambient;

    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * albedoMap * light.diffuse;

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = spec * specularMap * light.specular;

    return ambient + diffuse + specular;
}

void main() {
    vec3 normal = vec3(texture(texture_normal1, uv));
    normal = normalize(normal * 2.0 - 1.0);

    vec3 albedo = vec3(texture(texture_diffuse1, uv));
    vec3 specular = vec3(texture(texture_specular1, uv));

    vec3 viewDir = normalize(tangentViewPos - tangentFragPos);

    vec3 finalColor = calcDirectionalLight(dirLight, normal, viewDir, albedo, specular);
    //finalColor += calcPointLight(pointLight, norm, viewDir, fragPos, albedo, specular);
    //finalColor += calcSpotLight(spotLight, norm, viewDir, fragPos, albedo, specular);

    FragColor = vec4(finalColor, 1.0);
}