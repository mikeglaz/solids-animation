#include "platonic_solid.h"

PlatonicSolid::PlatonicSolid(std::vector<glm::vec3>&& vp, std::vector<Triangle>&& t) : Solid(std::move(vp)), initial_triangles(std::move(t))
{
  triangles = initial_triangles;
  build_solid();
}

float PlatonicSolid::tau(){
  return (1 + sqrt(5.0))/2.0;
}

void PlatonicSolid::fill_vertex_buffer(){
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, solid_vertices.size()*sizeof(Vertex), solid_vertices.data(), GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glEnableVertexAttribArray(0);
}

void PlatonicSolid::fill_normal_buffer()
{
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
  glBufferData(GL_ARRAY_BUFFER, solid_vertices.size()*sizeof(Vertex), solid_vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);
}

void PlatonicSolid::build_solid()
{
  for(auto& triangle : triangles){
    Vertex& v1 = vertices[triangle.v1];
    Vertex& v2 = vertices[triangle.v2];
    Vertex& v3 = vertices[triangle.v3];

    v1.pos = glm::normalize(v1.pos);
    v2.pos = glm::normalize(v2.pos);
    v3.pos = glm::normalize(v3.pos);

    glm::vec3 normal = get_normal(v1, v2, v3);
    v1.normal = v2.normal = v3.normal = normal;

    solid_vertices.push_back(v1);
    solid_vertices.push_back(v2);
    solid_vertices.push_back(v3);
  }

  fill_vertex_buffer();
  fill_normal_buffer();
}

void PlatonicSolid::draw()
{
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, solid_vertices.size());
  glBindVertexArray(0);
}

std::ostream& operator<<(std::ostream& os, const std::vector<Triangle>& triangles)
{
  for(auto& triangle : triangles){
    os << '[' << triangle.v1 << ',' << triangle.v2 << ',' << triangle.v3 << ']' << '\n';
  }

  return os;
}


