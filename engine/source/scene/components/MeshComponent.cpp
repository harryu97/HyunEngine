#include "MeshComponent.h"
#include "../../Engine.h"
#include "../../render/Material.h"
#include "../../render/Mesh.h"
#include "../../render/RenderQueue.h"
#include "../GameObject.h"
namespace eng {
void MeshComponent::Update(float deltaTime) {
  if (!m_mesh || !m_material) {
    return;
  }
  // If everthing is valid create render queue
  eng::RenderCommand command;
  command.material = m_material;
  command.mesh = m_mesh;
  command.modelMatrix =
      getOwner()->GetWorldTransform();  // ensure latest transform data

  auto& renderQueue = Engine::getInstance().getRenderQueue();
  renderQueue.Submit(command);
}
MeshComponent::MeshComponent(Material* material, Mesh* mesh) {
  m_material = material;
  m_mesh = mesh;
}

void MeshComponent::SetMaterial(Material* material) {
  m_material = material;
}

void MeshComponent::SetMesh(Mesh* mesh) {
  m_mesh = mesh;
}

void MeshComponent::LoadProperties(const nlohmann::json& json) {
  if (json.contains("material")) {
    auto& matObj = json["material"];
    const std::string path = matObj.value("path", "");
    auto mat = Material::Load(path);
    if (mat && matObj.contains("params")) {
      auto& paramObj = matObj["params"];

      if (paramObj.contains("float")) {
        for (auto& p : paramObj["float"]) {
          std::string name = p.value("name", "");
          float value = p.value("value", 0.0f);
          mat->SetParam(name, value);
        }
      }
      // float 2
      if (paramObj.contains("float2")) {
        for (auto& p : paramObj["float2"]) {
          std::string name = p.value("name", "");
          float value0 = p.value("value0", 0.0f);
          float value1 = p.value("value1", 0.0f);
          mat->SetParam(name, value0, value1);
        }
      }

      // float 3
      if (paramObj.contains("float3")) {
        for (auto& p : paramObj["float3"]) {
          std::string name = p.value("name", "");
          float value0 = p.value("value0", 0.0f);
          float value1 = p.value("value1", 0.0f);
          float value2 = p.value("value2", 0.0f);

          mat->SetParam(name, glm::vec3(value0, value1, value2));
        }
      }

      // Texture
      if (paramObj.contains("textures")) {
        for (auto& p : paramObj["textures"]) {
          std::string name = p.value("name", "");
          std::string texPath = p.value("path", "");
          Texture* texture = Texture::Load(texPath);
          mat->SetParam(name, texture);
        }
      }
    }
    SetMaterial(mat);
    // const std::string matPath = json.value("material", "");
    // auto material = Material::Load(matPath);
    // if (material) {
    //  SetMaterial(material);
    //}
  }
  if (json.contains("mesh")) {
    const auto& meshObj = json["mesh"];
    const std::string type = meshObj.value("type", "box");
    if (type == "box") {
      glm::vec3 extents(meshObj.value("x", 1.0f), meshObj.value("y", 1.0f),
                        meshObj.value("z", 1.0f));

      auto mesh = Mesh::CreateBox(extents);
      SetMesh(mesh);
    }
  }
}
}  // namespace eng
