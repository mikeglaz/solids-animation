#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_color;

out vec3 vert_color;
out vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * model * vec4(in_position, 1.0f);
  position = vec3(model * vec4(in_position, 1.0));
  vert_color = in_color;
}
