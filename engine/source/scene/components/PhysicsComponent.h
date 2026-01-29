#pragma once
#include <memory>
#include "../../physics/RigidBody.h"
#include "scene/Component.h"

namespace eng {
class PhysicsComponent : public Component {
  COMPONENT(PhysicsComponent)
 public:
  PhysicsComponent() = default;
  PhysicsComponent(const std::shared_ptr<RigidBody>& body);
  void LoadProperties(const nlohmann::json& json) override;
  void SetRigidBody(const std::shared_ptr<RigidBody>& body);
  const std::shared_ptr<RigidBody>& GetRigidBody();
  void Init() override;
  void Update(float deltaTime) override;

 private:
  std::shared_ptr<RigidBody> m_rigidBody;
};
}  // namespace eng
