#pragma once

#include <memory>
#include "../../Engine.h"
#include "../../input/InputManager.h"
#include "../../physics/KinematicCharacterController.h"
#include "../Component.h"
namespace eng {
class PlayerControllerComponent : public Component {
  COMPONENT(PlayerControllerComponent)
 public:
  void Init() override;
  void Update(float deltaTime) override;
  bool OnGround() const;

 private:
  // how fast mouse moves
  float m_sensitivity = 15.0f;
  float m_moveSpeed = 10.0f;

  float m_xRot = 0.0f;
  float m_yRot = 0.0f;
  std::unique_ptr<KinematicCharacterController> m_kinematicController;
};
}  // namespace eng
// namespace eng:
