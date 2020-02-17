#version 330 core

out vec4 out_color;

in vec3 normal;
in vec3 position;

void main()
{
  vec3 lamp_color = vec3(1.0f, 1.0f, 1.0f);
  vec3 light_pos = vec3(0.0f, 1.5f, 0.0f);

  // ambient;
  vec3 ambient = 0.2 * lamp_color;

  // diffuse
  vec3 light_dir = normalize(light_pos - position);
  float dot_product = max(dot(normal, light_dir), 0.0f);
  vec3 diffuse = dot_product * lamp_color;

  vec3 result = (ambient + diffuse) * lamp_color;

  out_color = vec4(result, 1.0f);
}
