#version 330 core

out vec4 out_color;

in vec3 normal;
in vec3 position;

uniform vec3 light_pos;
uniform vec3 view_pos;
uniform int light_type;

void main()
{
  vec3 light_color = vec3(1.0, 1.0, 1.0);
  vec3 object_color = vec3(0.0, 0.0, 1.0);

  // ambient
  vec3 ambient = 0.2 * light_color;

  // diffuse
  vec3 light_dir = normalize(light_pos - position);
  float dot_product = max(dot(normal, light_dir), 0.0);
  vec3 diffuse = dot_product * light_color;

  // // specular
  // vec3 view_dir = normalize(view_pos - position);
  // vec3 reflect_dir = reflect(-light_dir, normal);
  // float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 2);
  // vec3 specular = 0.5 * spec * light_color;

  vec3 result;

  if(light_type == 0){
    result = object_color;
  } else if(light_type == 1){
    result = ambient * object_color;
  } else if(light_type == 2){
    result = (ambient + diffuse) * object_color;
  }

  out_color = vec4(result, 1.0f);
}
