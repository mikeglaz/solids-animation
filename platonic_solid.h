#ifndef PLATONIC_SOLID_H
#define PLATONIC_SOLID_H

#include "solid.h"

struct Triangle{
  int v1;
  int v2;
  int v3;
};

class PlatonicSolid : public Solid{
protected:
  std::vector<Triangle> initial_triangles;
  std::vector<Triangle> triangles;
  std::vector<Vertex> solid_vertices;

  //methods
  void calculate_normals();
  void build_solid();
  void fill_vertex_buffer();
  void fill_normal_buffer();
  float tau();

public:
  PlatonicSolid(std::vector<glm::vec3>&&, std::vector<Triangle>&&);
  void transform_vertices(const glm::mat4&);
  void draw();
};

std::ostream& operator<<(std::ostream&, const std::vector<Triangle>&);

#endif
