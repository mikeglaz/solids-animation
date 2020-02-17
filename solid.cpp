#include "solid.h"

Solid::Solid()
{
  init_buffers();
}

Solid::Solid(std::vector<glm::vec3>&& vp) : vertex_positions(std::move(vp))
{
  init_buffers();
  fill_vertex_positions();
}

Solid::~Solid(){
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vertex_buffer);
  glDeleteBuffers(1, &normal_buffer);
}

void Solid::init_buffers()
{
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vertex_buffer);
  glGenBuffers(1, &normal_buffer);
}

void Solid::fill_vertex_positions(){
  for(auto pos : vertex_positions){
    Vertex vertex;
    vertex.pos = pos;
    vertices.push_back(vertex);
  }
}

void Solid::fill_vertex_buffer(){
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glEnableVertexAttribArray(0);
}

void Solid::fill_normal_buffer()
{
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);
}

glm::vec3 Solid::get_normal(const Vertex& v1, const Vertex& v2, const Vertex& v3){
  glm::vec3 edge1, edge2;
  glm::vec3 normal;

  edge1 = v2.pos - v1.pos;
  edge2 = v3.pos - v1.pos;

  normal = glm::cross(edge1, edge2);
  normal = glm::normalize(normal);

  return normal;
}

void Solid::draw()
{
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, vertices.size());
  glBindVertexArray(0);
}

std::ostream& operator<<(std::ostream& os, const std::vector<glm::vec3>& vertices){
  for(auto& vertex : vertices){
    os << vertex << '\n';
  }

  return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Vertex>& vertices){
  for(auto& vertex : vertices){
    os << "Vertex: " << vertex.pos << '\n';
    os << "Normal or Color: " << vertex.normal << "\n\n";
  }

  return os;
}

std::ostream& operator<<(std::ostream& os, const glm::mat4& matrix){
  os << '[';

  for(int col = 0; col < 4; col++){
    for(int row = 0; row < 4; row++){
      os << matrix[row][col];
      if(row < 3){
        os << ',';
      }
    }
    if(col < 3){
      os << ';';
    }
  }

  os << ']';

  return os;
}

std::ostream& operator<<(std::ostream& os, const glm::vec3 vector){
  os << '[' << vector.x << ';' << vector.y << ';' << vector.z << ']';

  return os;
}

std::ostream& operator<<(std::ostream& os, const Vertex& vertex){
  os << vertex.pos;

  return os;
}

glm::vec3 operator*(glm::mat4 matrix, glm::vec3 v){

  glm::vec4 vec4 = glm::vec4(v, 1.0f);
  glm::vec4 result = matrix * vec4;

  return result.xyz();
}
