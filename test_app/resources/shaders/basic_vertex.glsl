#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_UV;

out vec3 v_Normals;
out vec2 v_UV;

uniform mat4 u_Model;

void main()
{
  gl_Position = u_Model * vec4(a_Pos, 1.0);
  v_Normals = a_Normal;
  v_UV = a_UV;
}
