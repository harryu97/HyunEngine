#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <string>
#include <unordered_map>
#include "Texture.h"
namespace eng {
class ShaderProgram {
 public:
  ShaderProgram() = delete;
  ShaderProgram(const ShaderProgram&) = delete;
  ShaderProgram& operator=(const ShaderProgram&) = delete;
  ShaderProgram& operator=(ShaderProgram&) = delete;

  ~ShaderProgram();

  explicit ShaderProgram(GLuint shaderProgramId);
  void Bind();
  GLint GetUniformLocation(const std::string& name);
  // Setting Uniform Value
  void SetUniform(const std::string& name, float value);
  void SetUniform(const std::string& name, float v0, float v1);
  void SetUniform(const std::string& name, const glm::mat4& mat);
  void SetUniform(const std::string& name, const glm::vec3& value);
  void SetTexture(const std::string& name, Texture* texture);
  GLuint GetId() const;

 private:
  // use cache location to avoid extra openglCalls

  std::unordered_map<std::string, GLint> m_UniformLocationCache;
  GLuint m_ShaderProgram = 0;
  int m_currentTextureUnit = 0;
};
}  // namespace eng
