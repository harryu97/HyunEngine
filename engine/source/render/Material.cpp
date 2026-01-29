#include "Material.h"
#include <memory.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include "../Engine.h"
#include "../graphics/ShaderProgram.h"
#include "../graphics/Texture.h"
namespace eng {
void Material::SetShaderProgram(ShaderProgram* shaderProgram) {
  m_shaderProgram = shaderProgram;
}
void Material::SetParam(const std::string& name, float value) {
  m_floarParams[name] = value;
}
void Material::Bind() {
  if (!m_shaderProgram) {
    return;
  }
  m_shaderProgram->Bind();
  for (auto& param : m_floarParams) {
    m_shaderProgram->SetUniform(param.first, param.second);
  }
  for (auto& param : m_float2Params) {
    m_shaderProgram->SetUniform(param.first, param.second.first,
                                param.second.second);
  }
  for (auto& param : m_float3Params) {
    m_shaderProgram->SetUniform(param.first, param.second);
  }

  for (auto& param : m_textures) {
    m_shaderProgram->SetTexture(param.first, param.second);
  }
}
void Material::SetParam(const std::string& name, float v0, float v1) {
  m_float2Params[name] = {v0, v1};
}
void Material::SetParam(const std::string& name, const glm::vec3& value) {
  m_float3Params[name] = value;
}
ShaderProgram* Material::GetShaderProgram() {
  return m_shaderProgram;
}
void Material::SetParam(const std::string& name, Texture* texture) {
  m_textures[name] = texture;
}

Material* Material::Load(const std::string& path) {
  auto contents = Engine::getInstance().getFileSystem().LoadAssetFileText(path);
  if (contents.empty()) {
    return nullptr;
  }
  // pase json
  nlohmann::json json = nlohmann::json::parse(contents);
  Material* result;
  if (json.contains("shader")) {
    auto shaderObj = json["shader"];
    std::string vertexPath = shaderObj.value("vertex", "");
    std::string fragmentPath = shaderObj.value("fragment", "");
    auto& fs = Engine::getInstance().getFileSystem();
    auto vertexSrc = fs.LoadAssetFileText(vertexPath);
    auto fragmentSrc = fs.LoadAssetFileText(fragmentPath);

    auto& graphicsAPI = Engine::getInstance().getGraphicsAPI();
    auto ShaderProgram =
        graphicsAPI.CreateShaderProgram(vertexSrc, fragmentSrc);
    if (!ShaderProgram) {
      std::cout << "no sp" << std::endl;
      return nullptr;
    }

    std::cout << "✅ Created custom shader with ID: " << ShaderProgram->GetId()
              << std::endl;
    std::cout << "   Vertex shader path: " << vertexPath << std::endl;
    std::cout << "   Fragment shader path: " << fragmentPath << std::endl;
    result = new Material();
    result->SetShaderProgram(ShaderProgram);

    std::cout << "IT CONTAINS" << std::endl;
    if (json.contains("params")) {
      auto paramObj = json["params"];
      // float
      if (paramObj.contains("float")) {
        for (auto& p : paramObj["float"]) {
          std::string name = p.value("name", "");
          float value = p.value("value", 0.0f);
          result->SetParam(name, value);
        }
      }
      // float 2
      if (paramObj.contains("float2")) {
        for (auto& p : paramObj["float2"]) {
          std::string name = p.value("name", "");
          float value0 = p.value("value0", 0.0f);
          float value1 = p.value("value1", 0.0f);
          result->SetParam(name, value0, value1);
        }
      }

      // float 3
      if (paramObj.contains("float3")) {
        std::cout << "DEBUG: float3 exists" << std::endl;
        std::cout << "DEBUG: float3 type: " << paramObj["float3"].type_name()
                  << std::endl;
        std::cout << "DEBUG: float3 dump: " << paramObj["float3"].dump()
                  << std::endl;

        for (auto& p : paramObj["float3"]) {
          std::string name = p.value("name", "");
          std::cout << name << std::endl;
          float value0 = p.value("value0", 0.0f);
          float value1 = p.value("value1", 0.0f);
          float value2 = p.value("value2", 0.0f);

          result->SetParam(name, glm::vec3(value0, value1, value2));
        }
      }

      // Texture
      if (paramObj.contains("textures")) {
        for (auto& p : paramObj["textures"]) {
          std::string name = p.value("name", "");
          std::string texPath = p.value("path", "");
          Texture* texture = Texture::Load(texPath);
          result->SetParam(name, texture);
        }
      }
    }
  }
  return result;
}
}  // namespace eng
