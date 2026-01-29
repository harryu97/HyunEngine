#pragma once
#include <glm/vec3.hpp>
#include "../Component.h"
namespace eng {

// Light has two properties
//
class LightComponent : public Component {
  COMPONENT(LightComponent)
 public:
  void LoadProperties(const nlohmann::json& json) override;
  void Update(float deltaTime) override;
  void SetColor(const glm::vec3& color);
  const glm::vec3& GetColor() const;
  // Position comes from parent object so we dont store them
  // Color
 private:
  glm::vec3 m_color;
};
}  // namespace eng
