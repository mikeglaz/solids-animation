#ifndef SOLID_H
#define SOLID_H

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Vertex{
  glm::vec3 pos;
  glm::vec3 normal;
};

class Solid
{
protected:
  unsigned int vao;
  unsigned int vertex_buffer;
  unsigned int normal_buffer;

  std::vector<glm::vec3> vertex_positions;
  std::vector<Vertex> vertices;

  //methods
  void init_buffers();
  void fill_vertex_positions();
  void fill_vertex_buffer();
  void fill_normal_buffer();
  glm::vec3 get_normal(const Vertex&, const Vertex&, const Vertex&);


public:
  Solid();
  Solid(std::vector<glm::vec3>&&);
  ~Solid();
  virtual void draw();
};

std::ostream& operator<<(std::ostream&, const std::vector<glm::vec3>&);
std::ostream& operator<<(std::ostream&, const std::vector<Vertex>&);
std::ostream& operator<<(std::ostream&, const glm::mat4&);
std::ostream& operator<<(std::ostream&, const glm::vec3);
std::ostream& operator<<(std::ostream&, const Vertex&);
glm::vec3 operator*(glm::mat4, glm::vec3);

#endif
