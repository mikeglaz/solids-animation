#include "uv_sphere.h"

UVSphere::UVSphere(int ll) : Solid()
{
  if(ll <= MAX_LAT_LNG){
    lat_lng = ll;
  }

  generate_sphere();
  fill_vertex_buffer();
  fill_normal_buffer();
}

void UVSphere::generate_sphere()
{
  for(int i=0; i < lat_lng; i++){
    for(int j=0; j < lat_lng; j++){
      float theta0 = 2*M_PI/lat_lng * (i-1);
      float theta1 = 2*M_PI/lat_lng * i;
      // float theta2 = 2*M_PI/NUM_VERTICES * (i+1);
      float phi1 = M_PI/lat_lng * j;
      float phi2 = M_PI/lat_lng * (j+1);

      // // vertex 1
      // float x1 = cos(theta1) * sin(phi1);
      // float y1 = sin(theta1) * sin(phi1);
      // float z1 = cos(phi1);

      // // vertex 2
      // float x2 = cos(theta0) * sin(phi2);
      // float y2 = sin(theta0) * sin(phi2);
      // float z2 = cos(phi2);

      // // vertex 3
      // float x3 = cos(theta1) * sin(phi2);
      // float y3 = sin(theta1) * sin(phi2);
      // float z3 = cos(phi2);

      // // vertex 4
      // float x4 = cos(theta0) * sin(phi1);
      // float y4 = sin(theta0) * sin(phi1);
      // float z4 = cos(phi1);

      // vertex 1
      float x1 = cos(theta1) * sin(phi1);
      float y1 = sin(theta1) * sin(phi1);
      float z1 = cos(phi1);

      // vertex 2
      float x2 = cos(theta0) * sin(phi2);
      float y2 = sin(theta0) * sin(phi2);
      float z2 = cos(phi2);

      // vertex 3
      float x3 = cos(theta1) * sin(phi2);
      float y3 = sin(theta1) * sin(phi2);
      float z3 = cos(phi2);

      // vertex 4
      float x4 = cos(theta0) * sin(phi1);
      float y4 = sin(theta0) * sin(phi1);
      float z4 = cos(phi1);

      Vertex v1, v2, v3, v4;

      v1.pos = glm::vec3{x1,y1,z1};
      v2.pos = glm::vec3{x2,y2,z2};
      v3.pos = glm::vec3{x3,y3,z3};
      v4.pos = glm::vec3{x4,y4,z4};

      glm::vec3 normal = get_normal(v1, v2, v3);

      if(i < lat_lng && j < lat_lng-1){
        v1.normal = v2.normal = v3.normal = normal;

        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
      }

      normal = get_normal(v4, v2, v1);
      v4.normal = v2.normal = v1.normal = normal;

      vertices.push_back(v4);
      vertices.push_back(v2);
      vertices.push_back(v1);
    }
  }
}

void UVSphere::increase()
{
  if(lat_lng < MAX_LAT_LNG){
    lat_lng++;
    vertices.clear();
    generate_sphere();
    fill_vertex_buffer();
    fill_normal_buffer();
  }
}

void UVSphere::decrease()
{
  if(lat_lng > MIN_LAT_LNG){
    lat_lng--;
    vertices.clear();
    generate_sphere();
    fill_vertex_buffer();
    fill_normal_buffer();
  }
}
