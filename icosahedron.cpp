#include "icosahedron.h"


Icosahedron::Icosahedron(int r) : PlatonicSolid(
  {
    {  tau(),  0.0,  -1.0   },  // 0
    {  tau(),  0.0,   1.0   },  // 1
    { -tau(),  0.0,   1.0   },  // 2
    { -tau(),  0.0,  -1.0   },  // 3
    {  0.0,   -1.0,   tau() },  // 4
    {  0.0,    1.0,   tau() },  // 5
    {  0.0,    1.0,  -tau() },  // 6
    {  0.0,   -1.0,  -tau() },  // 7
    { -1.0,   -tau(), 0.0   },  // 8
    {  1.0,   -tau(), 0.0   },  // 9
    {  1.0,    tau(), 0.0   },  // 10
    { -1.0,    tau(), 0.0   },  // 11
  },
  {
    { 0,  1,  9 }, // 0
    { 0, 10,  1 }, // 1
    { 0,  6, 10 }, // 2
    { 0,  7,  6 }, // 3
    { 0,  9,  7 }, // 4

    { 9,  1,  4 }, // 5
    { 9,  4,  8 }, // 6
    { 9,  8,  7 }, // 7
    { 7,  8,  3 }, // 8
    { 2,  8,  4 }, // 9

    { 2,  3,  8 }, // 10
    { 2, 11,  3 }, // 11
    { 2,  5, 11 }, // 12
    { 2,  4,  5 }, // 13
    { 5,  4,  1 }, // 14

    { 5,  1, 10 }, // 15
    { 5, 10, 11 }, // 16
    { 6, 11, 10 }, // 17
    { 6,  3, 11 }, // 18
    { 6,  7,  3 }  // 19
  }), recursion_level(r) {
    if(recursion_level > 0 && recursion_level <= MAX_RECURSION_LEVEL){
      recurse();
      solid_vertices.clear();
      build_solid();
    }
}

void Icosahedron::recurse(){
  for(int i=0; i<recursion_level; i++){
    refine_triangles();
  }
}


void Icosahedron::reset()
{
  vertices.clear();
  solid_vertices.clear();
  if(face){
    triangles.clear();
    triangles.push_back(initial_triangles[0]);
  } else {
    triangles = initial_triangles;
  }
  fill_vertex_positions();
}

void Icosahedron::increase_recursion(){
  if(recursion_level < MAX_RECURSION_LEVEL){
    recursion_level++;
    reset();
    recurse();
    build_solid();
  }
}

void Icosahedron::decrease_recursion(){
  if(recursion_level > 0){
    recursion_level--;
    reset();
    recurse();
    build_solid();
  }
}

void Icosahedron::set_face(bool f){
  face = f;
  recursion_level = 0;
  reset();
  build_solid();
}

void Icosahedron::add_vertex(Vertex vertex){
  vertex.pos = glm::normalize(vertex.pos);
  vertices.push_back(vertex);
}

void Icosahedron::create_middle_vertex(Vertex v1, Vertex v2){
  Vertex middle_vertex;

  middle_vertex.pos = glm::vec3(
    (v1.pos.x + v2.pos.x) / 2.0,
    (v1.pos.y + v2.pos.y) / 2.0,
    (v1.pos.z + v2.pos.z) / 2.0);

  add_vertex(middle_vertex);
}

void Icosahedron::refine_triangles(){
  int index = vertices.size() - 1;

  std::vector<Triangle> temp_triangles;

  for(auto& triangle : triangles){
    Vertex v1 = vertices[triangle.v1];
    Vertex v2 = vertices[triangle.v2];
    Vertex v3 = vertices[triangle.v3];

    create_middle_vertex(v1, v2);
    int a = ++index;

    create_middle_vertex(v2, v3);
    int b = ++index;

    create_middle_vertex(v3, v1);
    int c = ++index;

    Triangle triangle1{triangle.v1, a, c};
    Triangle triangle2{triangle.v2, b, a};
    Triangle triangle3{triangle.v3, c, b};
    Triangle triangle4{a, b, c};

    temp_triangles.push_back(triangle1);
    temp_triangles.push_back(triangle2);
    temp_triangles.push_back(triangle3);
    temp_triangles.push_back(triangle4);

  }

  triangles = std::move(temp_triangles);
}

void Icosahedron::set_recursion_level(int value) {
  recursion_level = value;
  reset();
  recurse();
  build_solid();
}
