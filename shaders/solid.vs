#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

out vec3 normal;
out vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * model * vec4(in_position, 1.0);
  position = vec3(model * vec4(in_position, 1.0));
  normal = vec3(model * vec4(in_normal, 1.0));
}
