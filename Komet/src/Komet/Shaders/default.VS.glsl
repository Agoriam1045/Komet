#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 2) in vec3 a_Normal;
layout(location = 3) in vec2 a_TexCoord;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {
    v_FragPos = vec3(u_Model * vec4(a_Position, 1.0));
    v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal; // World-space normal
    v_TexCoord = a_TexCoord;

    gl_Position = u_Projection * u_View * vec4(v_FragPos, 1.0);
}