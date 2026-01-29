#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
namespace eng {
class ShaderProgram;
class Material;
class Mesh;
class GraphicsAPI {
 public:
  bool Init();
  ShaderProgram* CreateShaderProgram(const std::string& vertexSource,
                                     const std::string& fragmentSource);
  ShaderProgram* getDefaultShaderProgram();

  GLuint CreateVertexBuffer(const std::vector<float>& vertices);
  GLuint CreateIndexBuffer(const std::vector<uint32_t>& indices);

  void SetClearColor(float r, float g, float b, float a);
  void ClearBuffers();
  void BindShaderProgram(ShaderProgram* shaderProgram);
  void BindMaterial(Material* material);
  void BindMesh(Mesh* mesh);
  void UnbindMesh(Mesh* mesh);
  void DrawMesh(Mesh* mesh);

 private:
  ShaderProgram* m_defaultShaderProgram;
};
}  // namespace eng
