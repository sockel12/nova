#version 330 core

in vec3 v_Normals;
in vec2 v_UV;

out vec4 FragColor;

uniform vec3 u_Color;
uniform sampler2D u_Texture;

void main() { FragColor = texture(u_Texture, v_UV); }