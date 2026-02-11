#version 330 core
layout(location = 0) out vec4 color;

struct Material {
    sampler2D diffuse;   // The texture added
    vec3 specular;       // Color of the highlight
	float shininess;     // Self explanatory, shininess of the material
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 v_TexCoord;
in vec3 v_Normal;      // From Vertex Shader
in vec3 v_FragPos;     // From Vertex Shader (World Space)

uniform vec3 u_ViewPos; // Camera position for specular calc
uniform Material u_Material;
uniform Light u_Light;

void main() {
    //Ambient
    vec3 ambient = u_Light.ambient * texture(u_Material.diffuse, v_TexCoord).rgb;

    //Diffuse 
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_Light.position - v_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_Light.diffuse * diff * texture(u_Material.diffuse, v_TexCoord).rgb;

    //Specular
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    vec3 specular = u_Light.specular * (spec * u_Material.specular);

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0);
}