#pragma once
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <string>
#include "../graphics/VertexLayout.h"
namespace eng {
class Mesh {
 public:
  Mesh(const VertexLayout& layout,
       const std::vector<float>& vertices,
       const std::vector<uint32_t> indices);
  Mesh(const VertexLayout& layout, const std::vector<float>& vertices);
  Mesh(const Mesh&) = delete;
  Mesh& operator=(const Mesh&) = delete;
  Mesh& operator=(Mesh&) = delete;

  void Bind();
  void Draw();
  void UnBind();
  static Mesh* CreateBox(const glm::vec3& extents = glm::vec3(1.0f));
  static Mesh* CreateSphere(float radius, int sectors, int stacks);
  // static Mesh* Load(const std::string& path);

 private:
  VertexLayout m_vertexLayout;
  size_t m_VertexCount = 0;
  size_t m_indexCount = 0;
  GLuint m_VBO = 0;
  GLuint m_EBO = 0;
  GLuint m_VAO = 0;
};
}  // namespace eng
