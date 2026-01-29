#pragma once
#include <glm/vec3.hpp>
#include <memory>
#include <string>
#include <unordered_map>

namespace eng {
// Material class contains shader program
class ShaderProgram;
class Texture;
class Material {
 public:
  void SetShaderProgram(ShaderProgram* shaderProgram);
  void SetParam(const std::string& name, float value);
  void Bind();
  void SetParam(const std::string& name, const glm::vec3& value);
  void SetParam(const std::string& name, float v0, float v1);
  void SetParam(const std::string& name, Texture* texture);
  ShaderProgram* GetShaderProgram();

  static Material* Load(const std::string& path);

 private:
  ShaderProgram* m_shaderProgram;
  std::unordered_map<std::string, float> m_floarParams;
  std::unordered_map<std::string, std::pair<float, float>> m_float2Params;
  std::unordered_map<std::string, glm::vec3> m_float3Params;
  std::unordered_map<std::string, Texture*> m_textures;
};
}  // namespace eng
