#version 330 core

out vec4 out_color;

in vec3 vert_color;
in vec3 position;

uniform vec3 light_pos;
uniform vec3 view_pos;
uniform int light_type;

void main()
{
  vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
  vec3 normal = vec3(0.0f, 1.0f, 0.0f);

  // ambient
  vec3 ambient = 1.0f * light_color;

  // diffuse
  vec3 light_dir = normalize(light_pos - position);
  float dot_product = max(dot(normal, light_dir), 0.0f);
  vec3 diffuse = dot_product * light_color;

  // specular
  vec3 view_dir = normalize(view_pos - position);
  vec3 reflect_dir = reflect(-light_dir, normal);
  float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
  vec3 specular = 0.5 * spec * light_color;

  vec3 result;

  if(light_type == 0){
    result = vert_color;
  } else if(light_type == 1){
    result = ambient * vert_color;
  } else if(light_type == 2){
    result = (ambient + diffuse) * vert_color;
  }

  out_color = vec4(result, 1.0f);
}

// void main()
// {

//   vec3 light_color = vec3(1.0, 1.0, 1.0);
//   vec3 normal = vec3(0.0, 1.0, 0.0);
//   vec3 light_dir = vec3(2.0, 2.5, 1.0);

//   float strength = 0.5;
//   float shininess = 8.0;

//   vec3 ambient = 0.1f * light_color;
//   vec3 half_vector = light_pos + view_pos;

//   float diffuse = max(0.0, dot(normal, light_dir));
//   float specular = max(0.0, dot(normal, half_vector));

//   if(diffuse == 0.0){
//     specular = 0.0;
//   } else {
//     specular = pow(specular, shininess); // sharpen the highlight
//   }
//   vec3 scattered = ambient + light_color * diffuse;
//   vec3 reflected = light_color * specular * strength;

//   // vec3 rgb = min(object_color.rgb * scattered + reflected, vec3(1.0));
//   vec3 rgb = min(vert_color * scattered, vec3(1.0));
//   out_color = vec4(rgb, 1.0);
// }
