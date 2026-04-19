#version 330 core

in vec3 a_Pos;
in vec3 a_Normal;
in vec2 a_UV;

uniform mat4 u_Model;

void main() { gl_Position = u_Model * vec4(a_Pos, 1.0); }
