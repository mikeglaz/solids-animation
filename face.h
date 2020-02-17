#include <map>
#include <fstream>
#include "platonic_solid.h"

enum class NormalFaceType { regular_normal, average_normal };
// #include "icosahedron.h"

class Face : public PlatonicSolid {
private:
  const int MAX_RECURSION_LEVEL{4};
  int recursion_level{0};
  glm::mat4 transformation_matrix;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec3> normal_sums;
  NormalFaceType normal_type{NormalFaceType::regular_normal};

  // methods
  void create_middle_vertex(Vertex, Vertex);
  void add_vertex(Vertex);
  void refine_triangles();
  void recurse();
  void build_face();
  void reset();

public:
  Face(int);
  void set_recursion_level(int);
  void increase_recursion();
  void decrease_recursion();
  void set_normal_type(NormalFaceType);
};

