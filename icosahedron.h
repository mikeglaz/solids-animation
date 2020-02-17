#include <map>
#include <fstream>
#include "platonic_solid.h"

enum class NormalType { regular_normal, average_normal };

class Icosahedron : public PlatonicSolid {
private:
  const int MAX_RECURSION_LEVEL{4};
  int recursion_level{0};
  bool face{false};
  int face_index;
  glm::mat4 transformation_matrix;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec3> normal_sums;
  NormalType normal_type{NormalType::regular_normal};

  // methods
  void create_middle_vertex(Vertex, Vertex);
  void add_vertex(Vertex);
  void refine_triangles();
  void recurse();
  void build_face();
  void reset();

public:
  Icosahedron(int);
  void increase_recursion();
  void decrease_recursion();
  void set_face(bool);
  void set_normal_type(NormalType);
  void set_recursion_level(int);
};

