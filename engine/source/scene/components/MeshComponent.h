#pragma once

#include "../Component.h"

namespace eng {
class Material;
class Mesh;
class MeshComponent : public Component {
  COMPONENT(MeshComponent)

 public:
  MeshComponent() = default;
  // Constructor take mesh and material as pointer
  //
  MeshComponent(Material* material, Mesh* mesh);
  void Update(float deltaTime) override;
  void SetMaterial(Material* material);
  void SetMesh(Mesh* mesh);
  void LoadProperties(const nlohmann::json& json) override;

 private:
  Material* m_material;
  Mesh* m_mesh;
};

}  // namespace eng
